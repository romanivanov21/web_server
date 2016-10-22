/**
 *  Файл: daemon_tool_exception.h
 *
 *  Описание: класс daemon_tool_exception реализует тип исключений,
 *            которые могут возниктуть при перевдое программы в режим демона
 */

#ifndef _DAEMON_TOOL_EXCEPTION_H_
#define _DAEMON_TOOL_EXCEPTION_H_

#include "user_msg_parser.h"

#include <exception>

class daemon_tool_exception : public std::exception
{
public:
    daemon_tool_exception( msg_type msg ) noexcept;
    ~daemon_tool_exception() = default;

    /**
     * @brief получение информации об исключении
     *
     * @return информация об ошибке
     */
    const char* what() const noexcept override;
private:
    std::string msg_;
};

#endif //_DAEMON_TOOL_EXCEPTION_H_