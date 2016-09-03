#include "worker_process.h"

#include <iostream>

worker_process::worker_process()
{
    delegate1_= new delegate<void()>( [](){ std::cout<<"worker_process_start"<<std::endl; } );
    add_event( event::TEST, delegate1_ );
}

worker_process::~worker_process()
{
    delegate1_;
}

void worker_process::start_process() noexcept
{
    notify( event::TEST );
}