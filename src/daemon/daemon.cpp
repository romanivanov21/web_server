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

void daemon_tool::init_config()
{
    try
    {
        //!TODO функция не реализована
        server_config::get_instance().load_config_file("/../");
    }
    catch(...)
    {

    }
}

void daemon_tool::init_log()
{
    try
    {
        access_log::get_instance()->init_log_file("/var/log/web-server/access.log");
        error_log::get_instance()->init_log_file("/var/log/web-server/error.log");
    }
    catch(...)
    {

    }
}

void daemon_tool::start_daemon()
{
    std::unique_ptr<process_creator> process_creator(new daemon_process_creator());
    std::unique_ptr<process> process(process_creator->get_process());

    pid_t pid = process_creator->create_process();

    switch (pid)
    {
        case CHILD_PROCESS:
        {
            try
            {
                process->start_process();
            }
            catch (...)
            {

            }
            break;
        }

        case ERROR_PROCESS:
        {
            throw;
            break;
        }

        default:
        {
            const std::string pid_filename = "/var/run/web-server.pid";
            try
            {
                write_pid(pid, pid_filename);
            }
            catch (...)
            {

            }
            break;
        }
    }
}

void daemon_tool::write_pid(const int& pid, const std::string& pid_filename)
{
    FILE * stream = fopen(pid_filename.c_str(), "w+");
    if (!stream)
    {
        throw;
    }

    if (!fwrite((std::to_string(pid)).c_str(), (std::to_string(pid)).size(), 1, stream))
    {
        throw;
    }

    if (fclose(stream))
    {
        throw;
    }
}