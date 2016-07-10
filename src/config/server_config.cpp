#include "server_config.h"

#include <cassert>

server_config* server_config::s_cfg_ = nullptr;

server_config* server_config::get_instance( )
{
    if( s_cfg_ == nullptr )
    {
        s_cfg_ = new server_config( );
    }
    return s_cfg_;
}

bool server_config::find_cfg_file( const std::string &file_name ) noexcept
{
    assert( !file_name.empty() );
    file_name_ = file_name;
}

const std::string server_config::get_server_name( )
{
    throw;
    return "";
}

const std::string server_config::get_ip_address( )
{
    throw;
    return "";
}

const unsigned int server_config::get_port( )
{
    throw;
    return -1;
}

const std::string server_config::get_document_root( )
{
    throw;
    return "";
}

const std::string server_config::get_access_log( )
{
    throw;
    return "";
}

const std::string server_config::get_error_log( )
{
    throw;
    return "";
}
