/**
 *  Файл: server_log.h
 *
 *  Описание: реализация базовый функционал системы логирования
 */

#ifndef _SERVER_LOG_H_
#define _SERVER_LOG_H_

#include <string>

class server_log
{
public:
    server_log() = default;
    virtual ~server_log() = default;

    /**
     * @brief создание лог файла
     *
     * @param file_name директрия до лог файла
     *
     * @throw std::exception
     */
    virtual void init_log_file( const std::string & file_name ) = 0;

    /**
     * @brief сохранения лог в файл
     *
     * @param msg сообщение в записи
     */
    virtual void save_log( const std::string& msg ) = 0;

    server_log( const server_log& copy ) = delete;
    server_log & operator=( const server_log & copy ) = delete;

protected:
    /**
     * @brief получение даты и времени в необходимом формате типа string
     *
     * @return string строка со временем и датой
     */
    virtual const std::string get_data_time(void) noexcept;
    /**
     * @brief создание структуры записи( время записи, сообщение и т. д. ) в лог
     *
     * @return формированное сообщение
     */
    virtual const std::string create_log_struct( const std::string& msg ) noexcept;

protected:
    std::string access_log_filename_;
    std::string error_log_filename_;
};

#endif //_SERVER_LOG_H_