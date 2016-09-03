#include "server_config_exception.h"
#include "user_msg_parser.h"

server_config_exception::server_config_exception( const std::string &ex ) noexcept : ex_( ex ) { }

server_config_exception::server_config_exception( msg_type type ) noexcept :
  ex_( user_msg_parser::get_instance()->find_user_msg( type ) )
{
    assert( type < msg_type::msg_end );
}

const char* server_config_exception::what() const noexcept { return ex_.c_str(); }