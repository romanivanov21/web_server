/**
 *  Файл: thread_save_queue.h
 *
 *  Автор: Иванов Р. В.
 *
 *  Описание: реализация потокобезопосной очереди на базе std::queue,
 *            для хранения задач
 */

#ifndef _THREAD_SAVE_QUEUE_H_
#define _THREAD_SAVE_QUEUE_H_

#include <memory>
#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class thread_save_queue
{
public:
    thread_save_queue() = default;

    ~thread_save_queue() = default;

    /**
     *   @brief получение элемента из очереди, ожидается пока очередь пустая
     *
     *   @param value ссылка на переменную, куда будет записан элемент из очереди
     */
    void wait_and_pop(T& value)
    {
        std::unique_lock<std::mutex> lk(mut_);
        data_cond_.wait( lk, [this] { return !data_queue_.empty(); } );
        value = std::move( *data_queue_.front() );
        data_queue_.pop();
    }

    /**
     *   @brief попоытка получения элемента из очереди
     *
     *   @param value ссылка на переменную, куда будет записан элмемн из очереди
     *
     *   @return true если элемент удалось получить из очереди, false - иначе ( очередь пустая )
     */
    bool try_pop(T& value)
    {
        std::lock_guard<std::mutex> lk(mut_);
        if (data_queue_.empty())
            return false;
        value = std::move( *data_queue_.front() );
        data_queue_.pop();
        return true;
    }

    /**
     *   @brief получение элемента из очереди, ожидается пока очередь пустая
     *
     *   @return shared_ptr куда будет записан элемент из очереди
     */
    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> lk(mut_);
        data_cond_.wait(lk, [this] { return !data_queue_.empty(); } );
        std::shared_ptr<T> res = data_queue_.front();
        data_queue_.pop();
        return res;
    }

    /**
     *   @brief попоытка получения элемента из очереди
     *
     *   @return std::shared_ptr если элемент удалось получить из очереди, false std::shared_ptr
     *           будут содержать nullptr ( очередь пустая )
     */
    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lk( mut_ );
        if( data_queue_.empty() )
            std::shared_ptr<T>();
        std::shared_ptr<T> res = data_queue_.front();
        data_queue_.pop();
        return res;
    }

    /**
     *   @brief зписать переменную в очередь
     *
     *   @param new_value значение
     */
    void push( T new_value )
    {
        std::shared_ptr<T> data ( std::make_shared<T>( std::move( new_value ) ) );
        std::lock_guard<std::mutex> lk( mut_ );
        data_queue_.push( data );
        data_cond_.notify_one();
    }

    /**
     *   @brief проверка очередь не пустая
     *
     *   @return true, если очередь содержит элементы, false - иначе
     */
    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mut_);
        return data_queue_.empty();
    }

private:
    mutable std::mutex mut_;
    std::queue<std::shared_ptr<T> > data_queue_;
    std::condition_variable data_cond_;
};

#endif //_THREAD_SAVE_QUEUE_H_