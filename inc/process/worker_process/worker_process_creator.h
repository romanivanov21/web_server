/**
 * Флайл: worker_process_creator.h
 *
 * Описание: создатель мастер процесса
 */

#ifndef _WORKER_PROCESS_CREATOR_H_
#define _WORKER_PROCESS_CREATOR_H_

#include "process_creator.h"

class worker_process_creator : public process_creator
{
public:
    worker_process_creator() = default;
    ~worker_process_creator() = default;

    /**
     * @brief создание нового процеса
     *
     * @return pid нового процесса
     */
    pid_t create_process() noexcept override;

    /**
     * @brief создание нового экземпляра класса worker_process
     *
     * @return новый экземпляр класса worker_process
     */
    process* get_process() noexcept override;
};

#endif //_WORKER_PROCESS_CREATOR_H_