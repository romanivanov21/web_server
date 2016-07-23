#include "master_process.h"
#include "master_process_manager.h"

#include <iostream>

master_process::master_process()
{
    manager_ = new master_process_manager();
}

master_process::~master_process()
{
}

master_process* master_process::get_instance() noexcept
{
    static master_process process;
    return &process;
}

void master_process::start_process() noexcept
{
    std::cout<<"Master process was started!"<<std::endl;
    //!TODO функция не реализована
}

void master_process::set_config() noexcept
{
    //!TODO функция не реализована
}