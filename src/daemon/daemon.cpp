#include "types.h"
#include "daemon_process.h"
#include "daemon.h"
#include "error_log.h"
#include "access_log.h"
#include "server_config.h"
#include "process_creator.h"
#include "daemon_process_creator.h"
#include "current_system_info.h"
#include "server_config_exception.h"
#include "edit_directories.h"
#include "daemon_tool_exception.h"
#include "serevr_log_exception.h"

#include <cstring>

void daemon_tool::init_config()
{
    try
    {
        /* В настоящей реализации, файл конфигурации сервера
           находиться в папке ../web_server/settings/server_config.yaml
           директория вычисляется относительно испольняемного файла из папки /web_server/build/bin
        */
        std::string path = current_system_info::get_current_path();
        edit_directories::rm_last_folder( path );
        edit_directories::rm_last_folder( path );
        edit_directories::rm_last_folder( path );
        edit_directories::add_new_folder( path, "settings" );
        edit_directories::add_new_folder( path, "server_config.yaml" );
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

void daemon_tool::init_log()
{
    try
    {
        access_log::get_instance()->init_log_file(server_config::get_config()->server_.logs_.access_log_);
#ifdef _DEBUG
#endif //_DEBUG
        error_log::get_instance()->init_log_file(server_config::get_config()->server_.logs_.error_log_);
    }
    catch( const server_log_exception& ex )
    {
        throw ex;
    }
}

void daemon_tool::start_daemon() const
{
    std::unique_ptr<process_creator> process_creator = std::make_unique<daemon_process_creator>();
    std::unique_ptr<process> process( process_creator->get_process() );

    pid_t pid = process_creator->create_process();

    switch ( pid )
    {
        case process_creator::CHILD_PROCESS:
        {
            access_log::get_instance()->save_log( "Created process to control the demon" );
            process->start_process();
            break;
        }
        case process_creator::ERROR_PROCESS:
        {
            error_log::get_instance()->save_log( "Create process error" );
            throw daemon_tool_exception( msg_type::msg_system_error );
            break;
        }
        default:
        {
            const std::string pid_filename = "/var/run/web-server.pid";
            if( write_pid( pid, pid_filename ) )
            {
                access_log::get_instance()->save_log( "Save pid: " + std::to_string( pid ) + " to file" );
            }
            else
            {
                error_log::get_instance()->save_log( "Can not save pid: " + std::to_string( pid ) + " to file" );
                error_log::get_instance()->save_log("Stoped echo-server");
                kill(pid, SIGKILL);
                throw daemon_tool_exception( msg_type::msg_start_daemon_err );
            }
        }
    }
}

bool daemon_tool::write_pid( const int& pid, const std::string& pid_filename ) const noexcept
{
    assert( !pid_filename.empty() );

    FILE* stream = fopen( pid_filename.c_str(), "w+");
    bool res = false;
    if( stream )
    {
        res = ( fwrite( ( std::to_string( pid ) ).c_str(), 1, ( std::to_string( pid ) ).size(), stream ) == ( std::to_string( pid ) ).size() );
        fclose( stream );
    }
    return res;
}