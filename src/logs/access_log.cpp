#include "access_log.h"

#include <cassert>

access_log & access_log::get_instance( ) noexcept
{
    static access_log log;
    return log;
}

void access_log::save_log( const std::string &msg )
{
    assert( !msg.empty() );
    assert( !file_name_.empty() );

    write_log_file( create_log_struct( msg ) );
}

const std::string& access_log::create_log_struct( const std::string &msg ) noexcept
{
    return msg;
}