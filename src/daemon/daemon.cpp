#include "types.h"
#include "daemon.h"
#include "error_log.h"
#include "access_log.h"
#include "server_config.h"
#include "master_process_creator.h"
#include "daemon_process_creator.h"

#include <memory>
#include <iostream>
#include <cstring>

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
        access_log::get_instance( ).create_log_file( "/../" );
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
        error_log::get_instance( ).create_log_file( "/../" );
    }
    catch(...)
    {
        throw;
    }
}

void daemon_tool::start_daemon()
{
    std::unique_ptr<process_creator> process_creator(new daemon_process_creator());
    std::unique_ptr<process> process(process_creator->get_process());

    pid_t pid = process_creator->create_process();

    switch (pid)
    {
        case CHILD:
        {
            process->start_process();
            break;
        }

        case ERROR:
        {
            throw std::runtime_error(strerror(errno));
        }

        default:
        {
            const std::string pid_filename = "/var/run/echo-server.pid";
            write_pid(pid, pid_filename);
            break;
        }
    }
}

void daemon_tool::write_pid(const int & pid, const std::string & pid_filename)
{
    const std::string str_pid = std::to_string(pid);

    FILE * stream = fopen(pid_filename.c_str(), "w+");
    if (!stream)
    {
        throw std::runtime_error(strerror(errno));
    }

    if (!fwrite(str_pid.c_str(), str_pid.size(), 1, stream))
    {
        throw std::runtime_error(strerror(errno));
    }

    if (fclose(stream))
    {
        throw std::runtime_error(strerror(errno));
    }
}