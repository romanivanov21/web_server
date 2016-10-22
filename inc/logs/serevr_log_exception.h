/**
 *  Файл: server_log_exception.h
 *
 *  Описание: класс server_log_exception реализует тип исключений,
 *            которые могут возниктуть при создании лог файлов
 */

#ifndef _SERVER_LOG_EXCEPTION_H_
#define _SERVER_LOG_EXCEPTION_H_

#include "msg_type.h"

#include <string>
#include <exception>

class server_log_exception : public std::exception
{
public:
    server_log_exception( msg_type msg ) noexcept;
    ~server_log_exception() = default;

    /**
     * @brief получение информации об исключении
     *
     * @return информация об ошибке
     */
    const char* what() const noexcept override;
private:
    std::string msg_;
};
#endif //_SERVER_LOG_EXCEPTION_H_