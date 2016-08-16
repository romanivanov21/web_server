#include "server_log.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <stdexcept>

void server_log::create_log_file( const std::string &file_name )
{
    assert( file_name.empty() );

    std::ofstream stream;
    stream.open( file_name, std::ios::out );
    if( !stream )
        throw std::runtime_error("Can not create log file");
    file_name_ = file_name;
}

void server_log::write_log_file( const std::string &msg ) const
{
    assert( !msg.empty() );

    std::ofstream stream;
    assert( !file_name_.empty() );
    if( file_name_.empty() )
    {
        stream.open( file_name_,std::ios::app );
        if( !stream )
            throw std::runtime_error( "Can not find log file" );
        stream.write( msg.c_str(), msg.size() );
    }
}