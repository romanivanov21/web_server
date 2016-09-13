#include "edit_directories.h"

void edit_directories::rm_last_folder( std::string &path )
{
    assert( !path.empty() );

    size_t found = path.rfind( '/' );
    if( found != std::string::npos )
        path.erase( found );
}

void edit_directories::add_new_folder( std::string &dir, const std::string &value )
{
    assert( !dir.empty() );

    dir += "/";
    dir += value;
}