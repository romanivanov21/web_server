/**
 *  Файл: show_base.h
 *
 *  Описание: интерферйс для выода информации
 */

#include <string>

#ifndef _SHOW_BASE_H_
#define _SHOW_BASE_H_

class show_base
{
public:
    virtual ~show_base() = default;
    /**
     *  @brief вывод сообщения типа std::string
     *
     *  @param msg сообщение для выода
     */
    virtual void show_msg( const std::string& msg ) noexcept = 0;

    /**
     *  @brief вывод сообщения типа const char*
     *
     *  @param msg сообщение для вывода
     */

    virtual void show_msg( const char* msg ) noexcept = 0;

    show_base( const show_base& copy ) = delete;
    show_base& operator=( const show_base& copy ) = delete;

protected:
    show_base() = default;
};

#endif //_SHOW_BASE_H_