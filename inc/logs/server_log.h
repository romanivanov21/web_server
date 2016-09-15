/**
 *  Файл: server_log.h
 *
 *  Описание: реализация базовый функционал системы логирования
 */

#ifndef _SERVER_LOG_H_
#define _SERVER_LOG_H_

#include <string>
#include <mutex>

#define DATA_TIME_SIZE 80

class server_log
{
public:
    server_log() = default;
    virtual ~server_log() = default;

    /**
     * @brief сохранение идентификатора для доступа к log файлу
     *
     * @param file_name директрия до лог файла
     *
     * @throw std::exception
     */
    virtual void init_log_file( const std::string& file_name ) = 0;

    /**
     * @brief сохранение лога в файл
     *
     * @param msg сообщение в записи
     */

    virtual bool save_log( const std::string& msg ) const noexcept;

    /**
    * @brief создание структуры записи(время записи, сообщение и т. д.) в лог
    *
    * @return формированное сообщение
    */
    virtual const std::string create_log_struct( const std::string& msg ) const noexcept;

    /**
     * @brief получение даты и времени в необходимом формате типа string
     *
     * @return string строка со временем и датой
     */

    std::string get_data_time() const noexcept;

    server_log(const server_log& copy) = delete;
    server_log& operator=(const server_log& copy) = delete;

protected:
    /*имя лог файла */
    std::string filename_;

private:
    /*мьютекс для безопасного доступа к лог файлу*/
    mutable std::mutex mut_;
};

#endif //_SERVER_LOG_H_