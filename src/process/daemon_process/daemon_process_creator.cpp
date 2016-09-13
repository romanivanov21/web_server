#include "daemon_process.h"
#include "daemon_process_creator.h"

#include <unistd.h>

pid_t daemon_process_creator::create_process() noexcept
{
    return fork();
}

process* daemon_process_creator::get_process() noexcept
{
    return new daemon_process();
}