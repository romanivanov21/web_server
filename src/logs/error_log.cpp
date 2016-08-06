#include "error_log.h"

#include <cassert>
#include <stdexcept>
#include <fstream>

error_log& error_log::get_instance() noexcept
{
    static error_log err_log;
    return err_log;
}

const std::string& error_log::create_log_struct( const std::string &msg ) noexcept
{
    return msg;
}

void error_log::save_log( const std::string &msg )
{
    assert( !msg.empty() );
    write_log_file( create_log_struct( msg ) );
}