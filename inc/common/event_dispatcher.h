/**
 *   Файл: event_dispatcher.h
 *
 *	 Описание: Реализация класса диспейчер событий
 */
#ifndef _EVENT_DISPATCHER_H_
#define _EVENT_DISPATCHER_H_

#include "delegate.h"
#include "event.h"

#include <map>
#include <vector>

class event_dispatcher
{
public:
    event_dispatcher() = default;
    virtual ~event_dispatcher() noexcept;

protected:
    /**
     * @brief подписка на событие
     *
     * @param e событие
     * @param delegate указатель на делегат события
     *
     * @return void
     */
    template<class T>
    void add_event( event e, T* delegate ) noexcept;

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
    template<class... Args>
    void notify( event e, Args... args ) noexcept;

public:
    event_dispatcher( const event_dispatcher& copy ) = delete;
    event_dispatcher& operator=( const event_dispatcher& copy ) = delete;

private:
    typedef std::map< event, std::vector<delegate_base*> > event_table;
    event_table e_table_;
};
#include "event_dispatcher_impl.h"
#endif //_EVENT_DISPATCHER_H_