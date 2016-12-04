#include "worker_process.h"

#include <iostream>

worker_process::worker_process()
{
    delegate1_= new delegate<void()>( [](){ std::cout<<"worker_process_start"<<std::endl; } );
    event_dispatcher::add_event( event::TEST, delegate1_ );
}

worker_process::~worker_process()
{
    delete delegate1_;
}

void worker_process::start_process() noexcept
{
    event_dispatcher::notify( event::TEST );
}