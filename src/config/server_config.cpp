#include "server_config.h"
#include "server_config_exception.h"

#include <cassert>

server_config::server_config( )
{
    cfg_ = new CONFIG_TYPES();
}

server_config::~server_config( )
{
    delete cfg_;
}

server_config& server_config::get_instance( ) noexcept
{
    static server_config s_cfg_;
    return s_cfg_;
}

const CONFIG_TYPES* server_config::get_config( ) const
{
    return cfg_;
}

void server_config::load_config_file( const std::string &file_name )
{
    assert( !file_name.empty() );
    try
    {
        cfg_->SERVER_NAME_ = get_server_name( file_name );
        cfg_ -> IP_ADDRESS_ = get_ip_address( file_name );
        cfg_ -> PORT_ = get_port( file_name );
        cfg_ -> DOCUMENT_ROOT_ = get_document_root( file_name );
        cfg_ -> ERROR_LOG_ = get_error_log( file_name );
        cfg_ -> ACCESS_LOG_ = get_access_log( file_name );
    }
    catch( const server_config_exception& ex )
    {
        throw ex;
    }
}

const std::string server_config::get_server_name( const std::string &file_name )
{
    throw;
    return "";
}

const std::string server_config::get_ip_address( const std::string &file_name )
{
    throw;
    return "";
}

const unsigned int server_config::get_port( const std::string &file_name )
{
    throw;
    return -1;
}

const std::string server_config::get_document_root( const std::string &file_name )
{
    throw;
    return "";
}

const std::string server_config::get_access_log( const std::string &file_name )
{
    throw;
    return "";
}

const std::string server_config::get_error_log( const std::string &file_name )
{
    throw;
    return "";
}
