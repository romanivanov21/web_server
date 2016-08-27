#ifndef _USER_MSG_PARSER_H_
#define _USER_MSG_PARSER_H_

#include "msg_type.h"
#include "singleton_destroyer.h"

#include <string>

class user_msg_parser
{
public:
    user_msg_parser() = default;
    virtual ~user_msg_parser() = default;

    static user_msg_parser* get_instance() noexcept;

    virtual const std::string& find_user_msg( msg_type msg ) const noexcept = 0;

    user_msg_parser( const user_msg_parser& copy ) = delete;
    user_msg_parser& operator=( const user_msg_parser& copy ) = delete;

private:
    static user_msg_parser* instance_;
    static singleton_destroyer<user_msg_parser> destroyer_;
};

#endif //_USER_MSG_PARSER_H_