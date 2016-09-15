#include "server_config.h"
#include "server_config_exception.h"
#include "edit_directories.h"
#include "types.h"

#include <cstring>

destroyer_singleton<server_config> server_config::destroyer_;

config_struct* server_config::cfg_ = nullptr;

server_config* server_config::instance_ = nullptr;

server_config::server_config() noexcept
{
    if( cfg_ == nullptr )
    {
        cfg_ = new config_struct();
    }
}

server_config::~server_config() noexcept
{
    if( cfg_ )
    {
        delete cfg_;
    }
}

server_config* server_config::get_instance() noexcept
{
    if( instance_ == nullptr )
    {
        instance_ = new server_config();
        destroyer_.init_obj( instance_ );
    }
    return instance_;
}

const config_struct* server_config::get_config() noexcept
{
    assert( cfg_ );
    return cfg_;
}

void server_config::check_config_struct( const std::unique_ptr<embedding_python_api> &python )
{
    assert( python.get() );

    try
    {
        check_server_struct( python );
        check_connection_struct( python );
        check_directories_struct( python );
        check_logs_struct( python );
    }
    catch( server_config_exception& ex )
    {
        throw ex;
    }
}

void server_config::check_server_struct( const std::unique_ptr<embedding_python_api> &python )
{
    assert( python.get() );

    bool res = false;
    python->py_class_method_call( "check_server", res, nullptr, nullptr );
    if( !res )
    {
        throw server_config_exception( msg_type::msg_server_not_found );
    }
}

void server_config::check_connection_struct( const std::unique_ptr<embedding_python_api> &python )
{
    assert( python.get() );

    bool res = false;
    python->py_class_method_call( "check_connection", res, nullptr, nullptr );
    if( !res )
    {
        throw server_config_exception( msg_type::msg_connection_not_found );
    }
}

void server_config::check_directories_struct( const std::unique_ptr<embedding_python_api> &python )
{
    assert( python.get() );

    bool res = false;
    python->py_class_method_call( "check_directories", res, nullptr, nullptr );
    if( !res )
    {
        throw server_config_exception( msg_type::msg_directories_not_found );
    }
}

void server_config::check_logs_struct( const std::unique_ptr<embedding_python_api> &python )
{
    assert( python.get() );

    bool res = false;
    python->py_class_method_call( "check_logs", res, nullptr, nullptr );
    if( !res )
    {
        throw server_config_exception( msg_type::msg_logs_not_found );
    }
}

void server_config::load_config_file( const std::string& file_name )
{
    assert( !file_name.empty() );

    //создание объекта для встраивании модуля python
    std::unique_ptr<embedding_python_api> python = std::make_unique<embedding_python_api>();
    python->py_set_module_path( py_module_path_ );
    python->py_import_module( py_module_name_ );
    //создание новго объекта класса из модуля python
    python->py_class_instance( py_class_name_ );
    //вызов метода "load_config" из модуля python для чтения и загрузки конфигурацинного файла
    bool res = false;
    python->py_class_method_call( "load_config", res, const_cast<char *>( "(s)" ),
                                          const_cast<char *>( file_name.c_str() ) );
    if( !res )
    {
        throw server_config_exception( msg_type::msg_config_error );
    }

    try
    {
        check_config_struct( python );
        get_server_name( python );
        get_ip_version ( python );
        get_ip_address ( python );
        get_listen( python );
        get_document_root( python );
        get_access_log( python );
        get_error_log( python );
        get_mod_CGI( python );
    }
    catch( server_config_exception& ex )
    {
        throw ex;
    }
}

void server_config::get_server_name( const std::unique_ptr<embedding_python_api>& python )
{
    assert( python.get() );

    std::string server_name = "";
    python->py_class_method_call( "get_server_name", server_name, nullptr, nullptr );
    if( server_name != "" )
    {
        cfg_->server_.name_ = server_name;
    }
    else
    {
        throw server_config_exception( msg_type::msg_server_name_error );
    }
}

void server_config::get_ip_version( const std::unique_ptr<embedding_python_api>& python )
{
    assert( python.get() );

    std::string ip_version = "";
    python->py_class_method_call( "get_ip_version", ip_version, nullptr, nullptr );

    if( ip_version != "" )
    {
        size_t ip_version_temp = static_cast<size_t >( atoi( ip_version.c_str() ) );
        if( ip_version_temp == config_server::server_connection::CONFIG_IPv4 )
        {
            cfg_->server_.connection_.ip_version_ = config_server::server_connection::CONFIG_IPv4;
        }
        else if( ip_version_temp == config_server::server_connection::CONFIG_IPv6 )
        {
            cfg_->server_.connection_.ip_version_ = config_server::server_connection::CONFIG_IPv6;
        }
        else
        {
            throw server_config_exception( msg_type::msg_not_valid_ip );
        }
    }
    else
    {
        throw server_config_exception( msg_type::msg_ip_version_error );
    }
}

void server_config::get_ip_address( const std::unique_ptr<embedding_python_api> &python )
{
    assert( python.get() );

    std::string ip_address = "";
    python->py_class_method_call( "get_ip_address", ip_address, nullptr, nullptr );
    if( ( ip_address != "")
        && ( config_server::server_connection::is_valid_ip_address( ip_address, cfg_->server_.connection_.ip_version_ ) )
      )
    {
        cfg_->server_.connection_.ip_address_ = ip_address;
    }
    else
    {
        throw server_config_exception( msg_type::msg_ip_address_error );
    }
}

void server_config::get_listen( const std::unique_ptr<embedding_python_api> &python )
{
    assert( python.get() );

    std::string listen = "";
    python->py_class_method_call( "get_listen", listen, nullptr, nullptr );
    if( listen != "" )
    {
        std::uint32_t listen_temp = static_cast<std::uint32_t >( atoi( listen.c_str() ) );
        if( ( listen_temp > 0 ) && ( listen_temp < tcp_port_max ) )
        {
            cfg_->server_.connection_.listen_ = listen_temp;
        }
        else
        {
            throw server_config_exception( msg_type::msg_not_valid_listen );
        }
    }
    else
    {
        throw server_config_exception( msg_type::msg_listen_error );
    }
}

void server_config::get_document_root( const std::unique_ptr<embedding_python_api>& python )
{
    assert( python );

    std::string document_root = "";
    python->py_class_method_call( "get_document_root", document_root, nullptr, nullptr );
    if( document_root != "" )
    {
        cfg_->server_.directories_.document_root_ = document_root;
    }
    else
    {
        throw server_config_exception( msg_type::msg_document_root_error );
    }
}

void server_config::get_access_log( const std::unique_ptr<embedding_python_api>& python )
{
    assert( python );

    std::string access_log = "";
    python->py_class_method_call( "get_access_log", access_log, nullptr, nullptr );
    if( access_log != "" )
    {
        cfg_->server_.logs_.access_log_ = access_log;
    }
    else
    {
        throw server_config_exception( msg_type::msg_access_log_error );
    }
}

void server_config::get_error_log( const std::unique_ptr<embedding_python_api>& python )
{
    assert( python );

    std::string error_log = "";
    python->py_class_method_call( "get_error_log", error_log, nullptr, nullptr );
    if( error_log != "" )
    {
        cfg_->server_.logs_.error_log_ = error_log;
    }
    else
    {
        throw server_config_exception( msg_type::msg_error_log_error );
    }
}

void server_config::get_mod_CGI( const std::unique_ptr<embedding_python_api>& python )
{
    assert( python );

    python->py_class_method_call( "get_modules", cfg_->modules_.mod_, nullptr, nullptr );
}

const std::string server_config::get_py_module_path() noexcept
{
    std::string res = get_current_dir_name();
    edit_directories::rm_last_folder( res );
    edit_directories::rm_last_folder( res );
    edit_directories::add_new_folder( res, "src" );
    edit_directories::add_new_folder( res, "config" );

    return res;
}