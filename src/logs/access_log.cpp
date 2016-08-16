#include "access_log.h"

#include <cassert>
#include <fstream>
#include <string.h>

access_log * access_log::log = nullptr;
destroyer_access_log access_log::destroyer;

destroyer_access_log::~destroyer_access_log()
{
    delete log;
}

void destroyer_access_log::initialize( access_log * p )
{
    log = p;
}

access_log * access_log::get_instance() noexcept
{
    if (!log) {
        log = new access_log;
        destroyer.initialize(log);
    }

    return log;
}

void access_log::init_log_file( const std::string & file_name )
{
    assert( !file_name.empty() );
    access_log_filename_ = file_name;
}

void access_log::save_log( const std::string &msg )
{
    assert( !msg.empty() );

    std::string log_msg;
    try
    {
        log_msg = create_log_struct( msg );
    }
    catch(std::runtime_error & ex)
    {

    }

    std::ofstream stream;
    stream.open( access_log_filename_, std::ios::out | std::ios::app);
    if ( !stream )
    {
        throw std::runtime_error(strerror(errno));
    }

    stream.write(log_msg.c_str(), log_msg.size());
    stream.close();
}