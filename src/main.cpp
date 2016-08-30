/**
 *  Файл: main.cpp
 *
 *  Описание: реализация функции main - точка входа в приложение
 */

#include "daemon.h"
#include "server_config_exception.h"
#include "user_msg_parser.h"

#include <memory>
#include <iostream>

int main( int argc, char **argv )
{
    try
    {
        daemon_tool::init_config();
    }
    catch( server_config_exception& ex ) //Перехват исключений при чтении и разбора конфигурационного файла сервера
    {
        std::cout<<ex.what()<<std::endl;
    }
    catch( ... ) //Перехват всех типовх исключений
    {
        std::cout<<user_msg_parser::get_instance()->find_user_msg( msg_type::msg_system_error )<<std::endl;
    }

    try
    {
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
