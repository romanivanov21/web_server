/**
 *  Файл: console_show.h
 *
 *  Описание: класс для вывода информации на консоль, через стандартый поток ввода вывода
 */

#ifndef _CONSOLE_SHOW_H_
#define _CONSOLE_SHOW_H_

#include "destroyer_singleton.h"
#include "show_base.h"

class console_show : public show_base
{
public:
    ~console_show() = default;

    /**
     *  @brief создание единоственнного экземпляра класса console_show
     *
     *  @return указатель на экземпляр базового класса
     */
    static show_base* get_instance() noexcept;

    /**
     *  @brief вывод на консоль сообщения типа std::string
     *
     *  @param msg строка для вывода на консоль
     */
    void show_msg( const std::string& msg ) noexcept override;

    /**
     *  @brief вывод на консоль строки в Си
     *
     *  @param указатель на строку для вывода на консоль
     */
    void show_msg( const char* msg ) noexcept override;

    console_show( const console_show& copy ) = delete;
    console_show& operator=( const console_show& copy ) = delete;

private:
    console_show() = default;

private:
    friend class destroyer_singleton<console_show>;

    static destroyer_singleton<show_base> destroyer_;
    static console_show* console_;
};

#endif //_CONSOLE_SHOW_H_