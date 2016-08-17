#include "daemon.h"
#include "master_process_creator.h"
#include "server_config.h"
#include "access_log.h"
#include "error_log.h"
#include "types.h"

#include <fcntl.h>
#include <exception>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <stdexcept>
#include <memory>

daemon::daemon( )
{
}

daemon::~daemon( )
{
}

void daemon::init_config( )
{
    try
    {
        //!TODO функция не реализована
        server_config::get_instance( ).load_config_file( "/home/roman/work/C++ /web_server/settings/server_config.yaml" );
    }
    catch(...)
    {
        throw;
    }
}

void daemon::init_access_log( )
{
    try
    {
        //!TODO функция не реализована
        access_log::get_instance( ).create_log_file( "/../" );
    }
    catch(...)
    {
        throw;
    }
}

void daemon::init_error_log( )
{
    try
    {
        //!TODO функция не реализована
        error_log::get_instance( ).create_log_file( "/../" );
    }
    catch(...)
    {
        throw;
    }
}

void daemon::write_pid( int pid ) const
{
    const std::string num_pid = "/var/run/web-server.pid";
    int fd = open(num_pid.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if( fd > 0 )
    {
        const std::string str_pid = std::to_string( pid );
        int res = write( fd, str_pid.c_str( ), str_pid.size() );
        if( res != str_pid.size() )
        {
            close( fd );
            throw std::runtime_error("Can not save pid to file");
        }
        close( fd );
    }
}

void daemon::sighandler(int signum)
{
    waitpid(0, 0, WNOHANG);
}

void daemon::start_daemon()
{
    pid_t pid = default_error_code;
    pid_t sid = default_error_code;

    struct sigaction sa;

    std::shared_ptr<process_creator> proc_creator( new master_process_creator() );
    pid = proc_creator->create_process();
    std::shared_ptr<process> proc (proc_creator->get_process() );

    switch ( pid )
    {
        //кооиентарий
        case 0:
            try
            {
                proc->start_process( );
            }
            catch( std::runtime_error& ex )
            {
                throw ex;
            }
            break;

        case -1:
            throw std::runtime_error("fork error");
            break;

        default:
            write_pid( pid );
            print_to_console( "[ ok ] PID=" + std::to_string( pid ) );
            break;
    }
}

void daemon::print_to_console( const std::string &msg) const
{

}