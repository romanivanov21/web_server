#include "worker_pocess_creator.h"
#include "worker_process.h"

worker_process_creator::worker_process_creator()
{
}

worker_process_creator::~worker_process_creator()
{
}

process* worker_process_creator::get_process() noexcept
{
    return new worker_process();
}
