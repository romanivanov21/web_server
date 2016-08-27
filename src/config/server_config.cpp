#include "server_config.h"
#include "server_config_exception.h"
#include "types.h"

#include <cstring>

singleton_destroyer<server_config> server_config::destroyer_;

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
    std::unique_ptr<embedding_python_api> python( new embedding_python_api() );
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
    const char *buffer = nullptr;
    python->py_class_method_call( "get_server_name", &buffer, nullptr, nullptr );
    if( ( buffer ) && ( std::string(buffer) != "" ) )
    {
        cfg_->server_.name_ = buffer;
    }
    else
    {
        throw server_config_exception( msg_type::msg_server_name_error );
    }
}

void server_config::get_ip_version( const std::unique_ptr<embedding_python_api>& python )
{
    assert( python.get() );
    const char *buffer = nullptr;
    python->py_class_method_call( "get_ip_version", &buffer, nullptr, nullptr );

    if( ( buffer ) && ( std::string( buffer ) != "" ) )
    {
        size_t ip_version_temp = static_cast<size_t >( atoi( buffer ) );
        if( ( ip_version_temp == ip_version_type::CONFIG_IPv4 )
           || ( ip_version_temp == ip_version_type::CONFIG_IPv6 ) )
        {
            cfg_->server_.connection_.ip_version_ = ip_version_temp;
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
    const char *buffer = nullptr;
    python->py_class_method_call( "get_ip_address", &buffer, nullptr, nullptr );
    if( ( buffer ) && ( std::string( buffer ) != "" ) )
    {
        //TODO: Здесь должно быть проверка валидности ip адресса из конфигурационного файла
        cfg_->server_.connection_.ip_address_ = buffer;
    }
    else
    {
        throw server_config_exception( msg_type::msg_ip_address_error );
    }
}

void server_config::get_listen( const std::unique_ptr<embedding_python_api> &python )
{
    assert( python.get() );
    const char *buffer = nullptr;
    python->py_class_method_call( "get_listen", &buffer, nullptr, nullptr );
    if( ( buffer ) && ( std::string( buffer ) != "" ) )
    {
        std::uint32_t listen_temp = static_cast<std::uint32_t >( atoi( buffer ) );
        if( ( listen_temp > 0 ) && ( listen_temp < tcp_port_max ) )
        {
            cfg_->server_.connection_.listen_ = static_cast<size_t >( atoi( buffer ) );
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
    const char *buffer = nullptr;
    python->py_class_method_call( "get_document_root", &buffer, nullptr, nullptr );
    if( ( buffer ) && ( std::string( buffer ) != "" ) )
    {
        cfg_->server_.directories_.document_root_ = buffer;
    }
    else
    {
        throw server_config_exception( msg_type::msg_document_root_error );
    }
}

void server_config::get_access_log( const std::unique_ptr<embedding_python_api>& python )
{
    assert( python );
    const char *buffer = nullptr;
    python->py_class_method_call( "get_access_log", &buffer, nullptr, nullptr );
    if( ( buffer ) && ( std::string( buffer ) != "" ) )
    {
        cfg_->server_.logs_.access_log_ = buffer;
    }
    else
    {
        throw server_config_exception( msg_type::msg_access_log_error );
    }
}

void server_config::get_error_log( const std::unique_ptr<embedding_python_api>& python )
{
    assert( python );
    const char* buffer = nullptr;
    python->py_class_method_call( "get_error_log", &buffer,nullptr,nullptr );
    if( ( buffer ) && ( std::string( buffer ) != "" ) )
    {
        cfg_->server_.logs_.error_log_ = buffer;
    }
    else
    {
        throw server_config_exception( msg_type::msg_error_log_error );
    }
}

void server_config::get_mod_CGI( const std::unique_ptr<embedding_python_api>& python )
{
    assert( python );
    const char* buffer = nullptr;
    python->py_class_method_call( "get_modules", &buffer, nullptr, nullptr );
}

const std::string server_config::get_py_module_path() noexcept
{
    std::string res = get_current_dir_name();
    dell_last_dir( res );
    dell_last_dir( res );
    add_dir( res, "src" );
    add_dir( res, "config" );

    return res;
}