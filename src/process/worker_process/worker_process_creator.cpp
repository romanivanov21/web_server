#include "worker_process_creator.h"
#include "worker_process.h"

#include <sys/types.h>
#include <unistd.h>

pid_t worker_process_creator::create_process() noexcept
{
    return fork();
}
process* worker_process_creator::get_process() noexcept
{
    return new worker_process();
}
