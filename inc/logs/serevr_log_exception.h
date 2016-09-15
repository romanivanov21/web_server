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

    const char* what() const noexcept override;
private:
    std::string msg_;
};
#endif //_SERVER_LOG_EXCEPTION_H_