/**
 *   Файл: event_dispatcher.h
 *
 *   Описание: Реализация класса диспейчер событий
 */

#ifndef _EVENT_DISPATCHER_H_
#define _EVENT_DISPATCHER_H_

#include "delegate.h"
//#include "event.h"

#include <algorithm>
#include <cassert>
#include <map>
#include <vector>

template <class E>
class event_dispatcher
{
public:
    event_dispatcher() = default;

    virtual ~event_dispatcher() noexcept
    {
        std::for_each( e_table_.begin(), e_table_.end(), [&]( std::pair<E, std::vector<delegate_base*> > p )
        {
            std::for_each( p.second.begin(), p.second.end(), [&]( delegate_base* d )
            {
                delete d;
            });
        });
    }

    void remove_event( E e ) noexcept
    {
        auto it = e_table_.find( e );
        e_table_.erase( it );
    }

protected:
    /**
     * @brief подписка на событие
     *
     * @param e событие
     * @param delegate указатель на делегат события
     *
     * @return void
     */
    template <class T>
    void add_event( E e, T* del) noexcept
    {
        std::vector<delegate_base*>& v = e_table_[e];
        v.push_back( static_cast<delegate_base*>( del ) );
    }

    /**
     * @brief отписка от события
     *
     * @param e событие
     * @return void
     */
    void remove_event( event e ) noexcept;

    /**
     * @brief уведомление о произошедшем событии
     *
     * @param e событие, которое произошло
     * @param args аргументы функции, которую наужно передать
     *		  при вызове функции события
     * @return void
     */
    template <class... Args>
    void notify( E e, Args... args ) noexcept
    {

        std::vector<delegate_base*>& v = e_table_[e];
        for( auto& item : v )
        {
            ( static_cast<delegate<void(Args...)>*>( item ) )->operator()( args ...);
        }
    }

public:
    event_dispatcher( const event_dispatcher& copy ) = delete;
    event_dispatcher& operator=( const event_dispatcher& copy ) = delete;

private:
    typedef std::map< E, std::vector<delegate_base*> > event_table;
    event_table e_table_;
};
//#include "event_dispatcher_impl.h"
#endif //_EVENT_DISPATCHER_H_