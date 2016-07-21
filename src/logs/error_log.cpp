#include "error_log.h"

#include <cassert>

error_log& error_log::get_instance() noexcept
{
    static error_log err_log;
    return err_log;
}

void error_log::create_log_file( const std::string &dir )
{

}

void error_log::write_log( const std::string &log )
{

}