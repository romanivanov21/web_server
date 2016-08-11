/**
 * Флайл: daemon.h
 *
 * Описание: перевод программы в режим демона
 */

#ifndef _DAEMON_H_
#define _DAEMON_H_

#include <string>
#include <signal.h>

class daemon_tool
{
public:
    daemon_tool() = default;
    ~daemon_tool() = default;

    static void init_config();
    static void init_access_log();
    static void init_error_log();

    /**
     * @brief перевод программы в режим демона
     */
    void start_daemon();

    daemon_tool(const daemon_tool & copy) = delete;
    daemon_tool & operator=(const daemon_tool & copy) = delete;

private:
    /**
     * @brief состояния процесса
     */
    enum state_process { CHILD = 0, ERROR = -1 };
    /**
     * @brief запись  номера созданного процесса pid в файл
     *
     * @param pid номер созданного процесса
     *
     * @param pid_filename имя файла для записи pid
     */
    void write_pid(const int & pid, const std::string & pid_filename);

};

#endif //_DAEMON_H_