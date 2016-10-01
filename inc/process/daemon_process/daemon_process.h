/**
 * Флайл: daemon_process.h
 *
 * Описание: создание монитора процессов демона
*/

#ifndef _DAEMON_PROCESS_H_
#define _DAEMON_PROCESS_H_

#include "process.h"

#include <signal.h>

class daemon_process : public process
{
public:
    daemon_process() = default;
    ~daemon_process() = default;

    /**
     * @brief запуск монитора процессов и обработчика сигналов
     */
    void start_process() noexcept override;

    daemon_process(const daemon_process & copy) = delete;
    daemon_process & operator=(const daemon_process & copy) = delete;

private:
    /**
     * @brief регистрация сигналов обработчиком сигналов
     *
     * @param sigset набор сигналов
     * @param siginfo информация о сигналах
     */
    void setup_signal(sigset_t & sigset, siginfo_t & siginfo) noexcept;
};

#endif //_DAEMON_PROCESS_H_