#include "daemon.h"
#include "master_process_creator.h"
#include "daemon_process_creator.h"
#include "server_config.h"
#include "access_log.h"
#include "error_log.h"

#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <memory>


daemon_tool::daemon_tool( )
{
}

daemon_tool::~daemon_tool( )
{
}

void daemon_tool::init_config( )
{
    try
    {
        //!TODO функция не реализована
        server_config::get_instance( ).load_config_file( "/../" );
    }
    catch(...)
    {
        throw;
    }
}

void daemon_tool::init_access_log( )
{
    try
    {
        //!TODO функция не реализована
        access_log::get_instance()->set_log_dir("/../");
        access_log::get_instance()->create_log_file();
    }
    catch(...)
    {
        throw;
    }
}

void daemon_tool::init_error_log( )
{
    try
    {
        //!TODO функция не реализована
        error_log::get_instance()->set_log_dir("/../");
        error_log::get_instance( )->create_log_file();
    }
    catch(...)
    {
        throw;
    }
}

void daemon_tool::start_daemon()
{
    std::shared_ptr<process_creator> process_creator(new daemon_process_creator());
    std::shared_ptr<process> process(process_creator->get_process());

    pid_t pid = process_creator->create_process();

    switch (pid) {
        case 0:
        {
            process->start_process();
            break;
        }

        case -1:
        {
            break;
        }

        default:
        {
            std::string pid_filename = "/var/run/echo-server.pid";  //Создать файл конфигурации, откуда будет парситься путь!!!
            write_pid(pid, pid_filename);
            break;
        }
    }
}

void daemon_tool::write_pid(const int pid, const std::string & pid_filename)
{
    int fd = open(pid_filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0664);
    std::string str_pid = std::to_string(pid);
    write(fd, str_pid.c_str(), str_pid.size());
    close(fd);
}