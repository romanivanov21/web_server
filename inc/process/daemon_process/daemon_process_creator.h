/**
 * Флайл: daemon_process_creator.h
 *
 * Описание: создатель демона процесса
 */

#ifndef _DAEMON_PROCESS_CREATOR_H_
#define _DAEMON_PROCESS_CREATOR_H_

#include "process_creator.h"

class daemon_process_creator : public process_creator
{
public:
    daemon_process_creator() = default;
    ~daemon_process_creator() = default;

    /**
     * @brief создание нового процесса
     *
     * @return pid созданного процесса
     */
    pid_t create_process() noexcept override;

    /**
     * @brief получение монитора демона
     *
     * @return process * указатель на созданный объект монитора демона
     */
    process * get_process() noexcept override;


    daemon_process_creator(const daemon_process_creator & copy) = delete;
    daemon_process_creator & operator=(const daemon_process_creator & copy) = delete;
};

#endif //_DAEMON_PROCESS_CREATOR_H_