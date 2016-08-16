#include "error_log.h"

#include <cassert>
#include <fstream>
#include <string.h>

error_log * error_log::log = nullptr;
destroyer_error_log error_log::destroyer;

destroyer_error_log::~destroyer_error_log()
{
    delete log;
}

void destroyer_error_log::initialize( error_log * p )
{
    log = p;
}

error_log * error_log::get_instance() noexcept
{
    if (!log) {
        log = new error_log;
        destroyer.initialize(log);
    }

    return log;
}

void error_log::init_log_file( const std::string & file_name )
{
    assert( !file_name.empty() );
    error_log_filename_ = file_name;
}

void error_log::save_log( const std::string &msg )
{
    assert( !msg.empty() );

    std::string log_msg;
    try
    {
        log_msg = create_log_struct( msg );
    }
    catch(std::runtime_error & ex)
    {
        throw std::runtime_error(strerror(errno));
    }

    std::ofstream stream;
    stream.open( error_log_filename_, std::ios::out | std::ios::app);
    if ( !stream )
    {
        throw std::runtime_error(strerror(errno));
    }

    stream.write(log_msg.c_str(), log_msg.size());
    stream.close();
}