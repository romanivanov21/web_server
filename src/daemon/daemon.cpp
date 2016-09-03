#include "types.h"
#include "daemon.h"
#include "error_log.h"
#include "access_log.h"
#include "server_config.h"
#include "master_process_creator.h"
#include "daemon_process_creator.h"
#include "current_system_info.h"
#include "server_config_exception.h"

#include <cstring>

void daemon_tool::init_config()
{
    try
    {
        /* В настоящей реализации, файл конфигурации сервера
           находиться в папке ../web_server/settings/server_config.yaml
           директория вычисляется относительно испольняемного файла из папки web_server/build/bin
        */
        std::string path = current_system_info::get_current_path();
        dell_last_dir( path );
        dell_last_dir( path );
        dell_last_dir( path );
        add_dir( path, "settings" );
        add_dir( path, "server_config.yaml" );
        server_config::get_instance()->load_config_file( path );

#ifdef _DEBUG
        const config_struct* cfg = server_config::get_instance()->get_config();
        if( cfg )
            cfg->print_to_console();
#endif //_DEBUG
    }
    catch( const server_config_exception& ex )
    {
        throw ex;
    }
}

void daemon_tool::init_access_log( )
{
    try
    {
        //!TODO функция не реализована
        access_log::get_instance( ).create_log_file( server_config::get_config()->server_.logs_.access_log_ );
    }
    catch( std::runtime_error& ex )
    {
        std::cout<<ex.what()<<std::endl;
    }
}

void daemon_tool::init_error_log( )
{
    try
    {
        //!TODO функция не реализована
        error_log::get_instance( ).create_log_file( server_config::get_config()->server_.logs_.error_log_ );
    }
    catch(...)
    {
        throw;
    }
}

void daemon_tool::start_daemon()
{
    std::unique_ptr<process_creator> process_creator( std::make_unique<daemon_process_creator>() );
    std::unique_ptr<process> process(process_creator->get_process());

    pid_t pid = process_creator->create_process();

    switch (pid)
    {
        case CHILD_PROCESS:
        {
            try
            {
                access_log::get_instance().save_log( "Создан процесс для управления демоном" );
                process->start_process( );
            }
            catch (std::runtime_error & ex)
            {
                std::cout << ex.what( ) << std::endl;
            }
            break;
        }
        case ERROR_PROCESS:
        {
            throw std::runtime_error(strerror(errno));
            break;
        }

        default:
        {
            const std::string pid_filename = "/var/run/web-server.pid";
            try
            {
                write_pid( pid,pid_filename );
            }
            catch (std::runtime_error & ex)
            {
                std::cout << ex.what( ) << std::endl;
            }
            break;
        }
    }
}

void daemon_tool::write_pid(const int & pid, const std::string & pid_filename)
{
    FILE * stream = fopen(pid_filename.c_str(), "w+");
    if (!stream)
    {
        throw std::runtime_error(strerror(errno));
    }

    if (!fwrite((std::to_string(pid)).c_str(), (std::to_string(pid)).size(), 1, stream))
    {
        throw std::runtime_error(strerror(errno));
    }

    if (fclose(stream))
    {
        throw std::runtime_error(strerror(errno));
    }
}