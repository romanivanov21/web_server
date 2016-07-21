#include "access_log.h"

#include <cassert>

access_log& access_log::get_instance( ) noexcept
{
    static access_log log;
    return log;
}

void access_log::create_log_file( const std::string &dir )
{
    dir_ = dir;
}

void access_log::write_log( const std::string &log )
{
    assert( dir_.empty() );

    if( ( h_file_ = fopen( dir_.c_str(), "w" ) ) )
    {
        fwrite( log.c_str(), 1, log.length(), h_file_ );
        fclose( h_file_ );
    }
}