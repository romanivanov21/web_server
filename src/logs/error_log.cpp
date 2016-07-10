#include "error_log.h"

#include <cassert>

error_log* error_log::err_log_ = nullptr;

error_log* error_log::get_instance( )
{
    if( err_log_ == nullptr )
    {
        err_log_ = new error_log( );
    }
}

std::string error_log::get_dir( ) const noexcept { return dir_; }

void error_log::set_dir( std::string dir )
{
    assert( !dir.empty() );
    dir_ = dir;
}

void error_log::create_log_file( )
{
    throw;
}

void error_log::write( const std::string &str )
{
    assert( !str.empty() );
    throw;
}