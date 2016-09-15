/**
 *   Файл: destroyer_singleton.h
 *
 *   Опиасние: базовый класс для реализации паттерна синглтон,
 *             который предназначен для автоматического освобождения объекта
 */

#ifndef _DESTROYER_SINGLETON_H_
#define _DESTROYER_SINGLETON_H_

#include <cassert>

template <class T>
class destroyer_singleton
{
public:
    destroyer_singleton() = default;
    ~destroyer_singleton();

    void init_obj( T* obj ) noexcept;

    destroyer_singleton( const destroyer_singleton& copy ) = delete;
    destroyer_singleton& operator=( const destroyer_singleton& copy ) = delete;
private:
    T* obj_;
};

template <class T>
destroyer_singleton<T>::~destroyer_singleton()
{
    delete obj_;
}

template <class T>
void destroyer_singleton<T>::init_obj( T* obj ) noexcept
{
    assert( obj != nullptr );

    obj_ = obj;
}

#endif //_DESTROYER_SINGLETON_H_
