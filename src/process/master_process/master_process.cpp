#include "master_process.h"
#include "master_process_manager.h"
<<<<<<< HEAD

=======
#include "types.h"

#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <stdexcept>
#include <memory>
>>>>>>> origin/daemon
#include <iostream>

master_process::master_process()
{
    manager_ = new master_process_manager();
}

master_process::~master_process()
{
}

<<<<<<< HEAD
master_process* master_process::get_instance() noexcept
{
    static master_process process;
    return &process;
}

void master_process::start_process() noexcept
{
    std::cout<<"Master process was started!"<<std::endl;
    //!TODO функция не реализована
}

void master_process::set_config() noexcept
{
    //!TODO функция не реализована
=======
void master_process::start_process() noexcept
{
    pid_t sid = default_error_code;
    struct sigaction sa;
    std::memset(&sa, 0, sizeof(sa));

    sid = setsid();
    if (sid < 0)
    {
        throw std::runtime_error("Can not create master process");
    }

    chdir("/");

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    sa.sa_handler = sighandler;
    sigaction(SIGCHLD, &sa, 0);

}

void master_process::set_config() noexcept
{
    //!TODO функция не реализована
}

void master_process::sighandler( int signum )
{
    waitpid(0, 0, WNOHANG);
>>>>>>> origin/daemon
}