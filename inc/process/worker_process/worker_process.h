/**
 * Флайл: worker_process.h
 *
 * Описание: класс реализющий worker процесс
 */

#ifndef _WORKER_PROCESS_H_
#define _WORKER_PROCESS_H_

#include "process.h"
#include "event_dispatcher.h"

class worker_process : public process, protected event_dispatcher
{
public:
    worker_process();
    ~worker_process();

    /**
     * @brief точка входа в worker процесс
     */
    void start_process() noexcept override;

    worker_process( const worker_process &copy ) = delete;
    worker_process& operator=( const worker_process &copy ) = delete;

private:
    delegate<void()> *delegate1_;
};

#endif //_WORKER_H_