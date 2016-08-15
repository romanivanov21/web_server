#include "master_process_creator.h"
#include "master_process.h"

#include <unistd.h>

master_process_creator::master_process_creator()
{
}

master_process_creator::~master_process_creator()
{
}

pid_t master_process_creator::create_process() noexcept
{
    return fork();
}

process* master_process_creator::get_process() noexcept
{
    return new master_process();
}