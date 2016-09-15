/**
 *   Файл: user_msg_parser.h
 *
 *   Описание: базовый класс для обработки пользовательских сообщений
 *
 */

#ifndef _USER_MSG_PARSER_H_
#define _USER_MSG_PARSER_H_

#include "msg_type.h"
#include "destroyer_singleton.h"

#include <string>

class user_msg_parser
{
public:
    user_msg_parser() = default;
    virtual ~user_msg_parser() = default;

    /**
     *   @brief инстансирование синглетон класса
     *
     *   @return указатель на класс
     */
    static user_msg_parser* get_instance() noexcept;

    /**
     *   @brief абстрактный метод поиска пользовательского сообщения по интетификатору
     *
     *   @return пользовательское сообщение
     */
    virtual const std::string& find_user_msg( msg_type msg ) const noexcept = 0;

    user_msg_parser( const user_msg_parser& copy ) = delete;
    user_msg_parser& operator=( const user_msg_parser& copy ) = delete;

private:
    static user_msg_parser* instance_;
    static destroyer_singleton<user_msg_parser> destroyer_;
};

#endif //_USER_MSG_PARSER_H_