#include "access_log.h"

static access_log* access_log::acc_err_ = nullptr;

access_log* access_log::get_instance( )
{
    if( acc_log_ == nullptr )
    {
        acc_log_ = new access_log( );
    }

    return acc_log_;
}

void access_log::set_dir( std::string dir ) noexcept
{

}

std::string access_log::get_dir( ) const noexcept
{

}