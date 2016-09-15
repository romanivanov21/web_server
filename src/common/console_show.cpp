#include "console_show.h"

#include <iostream>
#include <cassert>

console_show* console_show::console_ = nullptr;

destroyer_singleton<show_base> console_show::destroyer_;

show_base* console_show::get_instance() noexcept
{
    if( console_ == nullptr )
    {
        console_ = new console_show();
        destroyer_.init_obj( console_ );
    }
    return console_;
}

void console_show::show_msg( const std::string &msg ) noexcept
{
    assert( !msg.empty() );

    std::cout<<msg<<std::endl;
}

void console_show::show_msg( const char *msg ) noexcept
{
    assert( msg != nullptr );

    std::cout<<msg<<std::endl;
}