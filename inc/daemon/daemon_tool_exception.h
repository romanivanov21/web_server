#ifndef _DAEMON_TOOL_EXCEPTION_H_
#define _DAEMON_TOOL_EXCEPTION_H_

#include "user_msg_parser.h"

#include <exception>

class daemon_tool_exception : public std::exception
{
public:
    daemon_tool_exception( msg_type msg ) noexcept;
    ~daemon_tool_exception() = default;

    const char* what() const noexcept override;
private:
    std::string msg_;
};

#endif //_DAEMON_TOOL_EXCEPTION_H_