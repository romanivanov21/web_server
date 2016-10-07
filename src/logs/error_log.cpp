#include <common/user_msg/msg_type.h>
#include "error_log.h"
#include "serevr_log_exception.h"
#include "types.h"

#include "sys/stat.h"

error_log* error_log::log = nullptr;
destroyer_singleton<error_log> error_log::destroyer;

error_log* error_log::get_instance() noexcept
{
    if ( !log )
    {
        log = new error_log;
        destroyer.init_obj( log );
    }
    return log;
}

void error_log::init_log_file( const std::string& file_name )
{
    assert( !file_name.empty() );

#ifdef _DEBUG
    int ret = mkdir("/var/log/echo-server", 0644);
    if (ret == default_error_code)
    {
        save_log( "Debug: can not create directory /var/log/echo-server" );
        save_log( "Debug: logfile initialization failed" );
        throw server_log_exception( msg_type::msg_init_error_log_err );
    }
    else if (ret == EEXIST)
    {
        save_log( "Debug: Directory already exists" );
    }
#endif //_DEBUG

    filename_ = file_name;

    if (!save_log("logfile initialization complete"))
    {
        throw server_log_exception( msg_type::msg_init_error_log_err );
    }
}
