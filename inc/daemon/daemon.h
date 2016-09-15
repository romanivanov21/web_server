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

    /**
     * @brief инициализация конфигурацию сервреа
     *
     * @throw server_config_exception
     */
    static void init_config();

    /**
     * @brief инициализция лог файлов
     *
     * @throw server_log_exception
     */
    static void init_log();

    /**
     * @brief перевод программы в режим демона
     *
     * @throw daemon_tools_error
     */
    void start_daemon() const;

    daemon_tool(const daemon_tool & copy) = delete;
    daemon_tool & operator=(const daemon_tool & copy) = delete;

private:
    /**
     * @brief запись  номера созданного процесса pid в файл
     *
     * @param pid_filename имя файла для записи номера pid
     *
     * @return true если успешно записно в файл, false иначе
     */
    bool write_pid( const int & pid, const std::string & pid_filename ) const noexcept;
};

#endif //_DAEMON_H_