#include "access_log.h"

access_log& access_log::get_instance( )
{
    static access_log acc_log;
    return acc_log;
}

void access_log::set_dir( std::string dir ) noexcept
{

}

std::string access_log::get_dir( ) const noexcept
{

}