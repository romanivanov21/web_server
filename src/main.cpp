/**
 *  Файл: main.cpp
 *
 *  Описание: реализация функции main - точка входа в приложение
 */

#include "daemon.h"
#include "server_config_exception.h"
#include "console_show.h"
#include "user_msg_parser.h"
#include "serevr_log_exception.h"
#include "daemon_tool_exception.h"

#include <memory>

int main(int argc, char* argv[])
{
    try
    {
        daemon_tool::init_config();
        daemon_tool::init_log();

        auto daemon = std::make_unique<daemon_tool>();
        daemon->start_daemon();
    }
    catch( const server_config_exception& ex ) //Обработка ошибок при чтении и разбора конфигурационного файла сервера
    {
        console_show::get_instance()->show_msg( ex.what() );
    }
    catch( const server_log_exception& ex )    //Обработка ошибок при содании лог файлов
    {
        console_show::get_instance()->show_msg( ex.what() );
    }
    catch( const daemon_tool_exception& ex )   //Обработка ошибок при переводе в режим демона
    {
        console_show::get_instance()->show_msg( ex.what() );
    }
    catch( ... )                               //Перехват всех типовх исключений ( нехватка памяти и т. д. )
    {
        console_show::get_instance()->show_msg(
          user_msg_parser::get_instance()->find_user_msg( msg_type::msg_system_error ) );
    }
    return 0;
}
