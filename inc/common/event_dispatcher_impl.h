/**
 * 	 Файл: event_dispatcher_impl.h
 *
 *	 Описание: реализация шаблонных методов класса
 *			   event_dispatcher
 *
 */

#ifndef _EVENT_DISPATCHER_IMPL_H_
#define _EVENT_DISPATCHER_IMPL_H_

#include <algorithm>
#include <cassert>

template<class T>
void event_dispatcher::add_event( event e, T* del) noexcept
{
    std::vector<delegate_base*>& v = e_table_[e];
    v.push_back( static_cast<delegate_base*>( del ) );
}

template <class... Args>
void event_dispatcher::notify( event e, Args... args ) noexcept
{
    assert( e != event::END_EVENTS );

    std::vector<delegate_base*>& v = e_table_[e];
    for( auto& item : v )
    {
        ( static_cast<delegate<void(Args...)>*>( item ) )->operator()( args ...);
    }
}

#endif //_OBSERVER_IMPL_H_