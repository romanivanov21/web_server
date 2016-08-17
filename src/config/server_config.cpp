#include "server_config.h"
#include "embedding_pyhton_api.h"
#include "server_config_exception.h"

#include <cstring>
#include <cassert>
#include <stdexcept>
#include <memory>

server_config& server_config::get_instance() noexcept
{
    static server_config s_cfg_;
    return s_cfg_;
}

const config_struct& server_config::get_config() const noexcept
{
    static config_struct cfg;
    std::memset( &cfg, 0x00, sizeof( cfg ) );
    return cfg;
}

void server_config::load_config_file( const std::string &file_name )
{
    assert( !file_name.empty() );

    std::unique_ptr<embedding_python_api> python( new embedding_python_api() );
    python->py_set_module_path( "/home/roman/work/C++ /web_server/src/config" );
    try
    {
        python->py_import_module( py_module_name_ );
    }
    catch( std::runtime_error &ex )
    {
        throw server_config_exception("");
    }
    python->py_function_call( "load_config", "%s", "/home/roman/work/C++ /web_server/src/settings/server_config.yaml" );
}

const std::string server_config::get_server_name( const std::string &file_name )
{
    return "";
}

const std::string server_config::get_ip_address( const std::string &file_name )
{
    throw;
    return "";
}

const size_t server_config::get_port( const std::string &file_name )
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
