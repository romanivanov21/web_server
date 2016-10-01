#include "master_process.h"
#include "master_process_manager.h"
#include "types.h"

#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <stdexcept>
#include <memory>
#include <iostream>

master_process::master_process()
{
    manager_ = new master_process_manager();
}

void master_process::start_process() noexcept
{
    
}

void master_process::set_config() noexcept
{
    //!TODO функция не реализована
}