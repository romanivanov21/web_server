/**
 *
 */

#include <string>

#ifndef _SHOW_BASE_H_
#define _SHOW_BASE_H_

class show_base
{
public:
    show_base() = default;
    virtual ~show_base() = default;

    virtual void show_msg( const std::string& msg ) noexcept = 0;
    virtual void show_msg( const char* msg ) noexcept = 0;

    show_base( const show_base& copy ) = delete;
    show_base& operator=( const show_base& copy ) = delete;
};

#endif //_SHOW_BASE_H_