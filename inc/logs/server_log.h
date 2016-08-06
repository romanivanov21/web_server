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
    virtual void create_log_file( const std::string &file_name );

    /**
     * @brief сохранения лог в файл
     *
     * @param msg сообщение в записи
     */
    virtual void save_log( const std::string& msg ) = 0;

    server_log( const server_log& copy ) = delete;
    server_log& operator=( const server_log& copy ) = delete;

protected:
    /**
     * @brief виртуальная функция создания
     *        структуры записи( время записи, сообщение и т. д. ) в лог
     *
     * @param msg сообщение в записи
     */
    virtual const std::string& create_log_struct( const std::string& msg ) noexcept = 0;

    /**
     * @brief запись в файл логгирования
     *
     * @param msg запись
     */
    virtual void write_log_file( const std::string& msg) const;
protected:
    std::string file_name_;
};

#endif //_SERVER_LOG_H_