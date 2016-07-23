/**
 * Флайл: worker_process_creator.h
 *
 * Описание:
 */

#ifndef _WORKER_PROCESS_CREATOR_H_
#define _WORKER_PROCESS_CREATOR_H_

#include "process_creator.h"

class worker_process_creator : public process_creator
{
public:
    worker_process_creator();
    ~worker_process_creator();

    pid_t create_process() noexcept override;
    process* get_process() noexcept override;
};

#endif //_WORKER_PROCESS_CREATOR_H_