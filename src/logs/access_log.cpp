#include "access_log.h"

#include <cassert>
#include <fstream>
#include <string.h>

access_log * access_log::log = nullptr;
destroyer_singleton<access_log> access_log::destroyer;

access_log * access_log::get_instance() noexcept
{
    if (!log)
    {
        log = new access_log;
        destroyer.initialize(log);
    }

    return log;
}

void access_log::init_log_file( const std::string & file_name )
{
    assert( !file_name.empty() );
    log_filename_ = file_name;
}

void access_log::save_log( const std::string & msg )
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
    stream.open( log_filename_, std::ios::out | std::ios::app);
    if ( !stream )
    {
        throw std::runtime_error(strerror(errno));
    }

    stream.write(log_msg.c_str(), log_msg.size());
    stream.close();
}