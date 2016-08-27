#ifndef _EN_USER_MSG_PARSER_H_
#define _EN_USER_MSG_PARSER_H_

#include "user_msg_parser.h"
#include "singleton_destroyer.h"

class en_user_msg_parser : public user_msg_parser
{
public:
    en_user_msg_parser() = default;
    ~en_user_msg_parser() = default;

    const std::string& find_user_msg( msg_type msg ) const noexcept override;

    en_user_msg_parser( const en_user_msg_parser& copy ) = delete;
    en_user_msg_parser& operator=( const en_user_msg_parser& copy ) = delete;
};

#endif //_EN_USER_MSG_PARSER_H_