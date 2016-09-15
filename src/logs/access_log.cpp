#include <common/user_msg/msg_type.h>
#include "serevr_log_exception.h"
#include "access_log.h"

access_log* access_log::log_ = nullptr;
destroyer_singleton<access_log> access_log::destroyer_;

access_log* access_log::get_instance() noexcept
{
    if ( !log_ )
    {
        log_ = new access_log();
        destroyer_.init_obj( log_ );
    }
    return log_;
}

void access_log::init_log_file( const std::string& file_name )
{
    assert( !file_name.empty() );

    filename_ = file_name;
    if ( !save_log( "logfile initialization complete" ) )
    {
        throw server_log_exception( msg_type::msg_init_access_log_err );
    }
}
