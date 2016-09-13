#include "event_dispatcher.h"

event_dispatcher::~event_dispatcher() noexcept
{
    std::for_each( e_table_.begin(), e_table_.end(), [&]( std::pair<event, std::vector<delegate_base*> > p )
    {
        std::for_each( p.second.begin(), p.second.end(), [&]( delegate_base* d )
        {
            delete d;
        });
    });
}

void event_dispatcher::remove_event( event e ) noexcept
{
    assert( e != event::END_EVENTS );
    auto it = e_table_.find( e );
    e_table_.erase( it );
}