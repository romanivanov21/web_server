/**
 * Флайл: worker_process.h
 *
 * Описание:
 */

#ifndef _WORKER_PROCESS_H_
#define _WORKER_PROCESS_H_

#include "process.h"

class worker_process : public process
{
public:
    worker_process();
    ~worker_process();

    void start_process() noexcept override;

    worker_process( const worker_process &copy ) = delete;
    worker_process& operator=( const worker_process &copy ) = delete;
};

#endif //_WORKER_H_