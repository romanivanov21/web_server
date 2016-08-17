/**
 *  Файл: main.cpp
 *
 *  Описание: реализация функции main - точка входа в приложение
 */

#include "daemon.h"

#include <memory>
#include <iostream>

int main( int argc, char **argv )
{
    try
    {
        daemon_tool::init_config( );
        daemon_tool::init_access_log( );
        daemon_tool::init_error_log( );
    }
    catch(...)
    {

    }

    std::shared_ptr<daemon_tool> daemon(new daemon_tool);
    try
    {
        daemon->start_daemon( );
    }
    catch (std::runtime_error & ex)
    {
        std::cout << ex.what( ) << std::endl;
    }

    return 0;
}
