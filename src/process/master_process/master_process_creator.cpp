#include "master_process_creator.h"
#include "master_process.h"

<<<<<<< HEAD
=======

>>>>>>> origin/daemon
#include <sys/types.h>
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
<<<<<<< HEAD
    return master_process::get_instance();
=======
    return new master_process();
>>>>>>> origin/daemon
}