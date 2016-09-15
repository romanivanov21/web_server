/**
 *  Файл: en_user_msg_parser.h
 *
 *  Описание: реализация интерфейса доасупа к пользовательским
 *            сообщениям на английском языке
 */

#ifndef _EN_USER_MSG_PARSER_H_
#define _EN_USER_MSG_PARSER_H_

#include "user_msg_parser.h"
#include "destroyer_singleton.h"

class en_user_msg_parser : public user_msg_parser
{
public:
    en_user_msg_parser() = default;
    ~en_user_msg_parser() = default;

    /**
     *  @brief поиск пользовательского сообщения по идентификатору
     *
     *  @param msg идентификатор сообщения
     *
     *  @return сообщение
     */
    const std::string& find_user_msg( msg_type msg ) const noexcept override;

    en_user_msg_parser( const en_user_msg_parser& copy ) = delete;
    en_user_msg_parser& operator=( const en_user_msg_parser& copy ) = delete;

private:
    static const std::string en_user_msg_[];
};

#endif //_EN_USER_MSG_PARSER_H_