/**
 * Флайл: master_process.h
 *
 * Описание: Класс реализует мастер процесс
 */

#ifndef _MASTER_PROCESS_H_
#define _MASTER_PROCESS_H_

#include "process.h"
#include "process_manager.h"
#include "master_process_manager.h"

class master_process : public process
{
public:
    master_process() = default;

    ~master_process() = default;

    /**
     * @brief точка входа в мастер процесс
     */
    void start_process() noexcept override;

    master_process( const master_process &copy ) = delete;
    master_process& operator=( const master_process &copy ) = delete;

private:
    master_process_manager manager_;
};

#endif //_MASTER_PROCESS_H_