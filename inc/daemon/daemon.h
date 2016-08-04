/**
 *  Файл: types.h
 *
 *  Описание: Класс для запуска демона
 */
#ifndef _DAEMON_H_
#define _DAEMON_H_

#include "process_creator.h"
#include "process.h"


#include <string>

class daemon
{
public:
    daemon();
    ~daemon();

    /**
     * @brief чтение и получение конфигурационного файла
     *
     * @param dir путь к конфиг файлу
     *
     * @throw std::runtime_exception
     */
    static void init_config( const std::string &dir );
    static void init_access_log();
    static void init_error_log();

    void start_daemon();


private:
    void write_pid( pid_t pid ) const;
    static void sighandler( int signum );
    void print_to_console( const std::string& msg) const;
};

#endif //_DAEMON_H_