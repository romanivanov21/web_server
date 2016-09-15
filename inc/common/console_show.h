/**
 *
 */

#ifndef _CONSOLE_SHOW_H_
#define _CONSOLE_SHOW_H_

#include "destroyer_singleton.h"
#include "show_base.h"

class console_show : public show_base
{
public:
    console_show() = default;
    ~console_show() = default;

    static show_base* get_instance() noexcept;
    void show_msg( const std::string& msg ) noexcept override;
    void show_msg( const char* msg ) noexcept override;

    console_show( const console_show& copy ) = delete;
    console_show& operator=( const console_show& copy ) = delete;

private:
    friend class destroyer_singleton<console_show>;

    static destroyer_singleton<show_base> destroyer_;
    static console_show* console_;
};

#endif //_CONSOLE_SHOW_H_