#include "types.h"
#include "process.h"
#include "daemon_process.h"
#include "process_creator.h"
#include "master_process_creator.h"

#include <memory>

#include <unistd.h>
#include <sys/wait.h>

void daemon_process::start_process() noexcept
{
    pid_t sid = default_error_code;

    sigset_t sigset;
    siginfo_t siginfo;

    sid = setsid();
    if(sid == default_error_code)
    {
        throw;
    }

    chdir("/");

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    setup_signal(sigset, siginfo);

    std::unique_ptr<process_creator> process_creator(new master_process_creator());
    std::unique_ptr<process> process(process_creator->get_process());

    pid_t pid = process_creator->create_process();

    switch(pid)
    {
        case process_creator::CHILD_PROCESS:
        {

            process->start_process();
            break;
        }

        case process_creator::ERROR_PROCESS:
        {
            break;
        }

        default:
        {
            sigwaitinfo(&sigset, &siginfo);         // ожидание поступления сигнала

            if(siginfo.si_signo == SIGCHLD)         // сигнал пришел от потомка
            {
                waitpid(pid, 0, WNOHANG);
                exit(EXIT_SUCCESS);
            }
            else if(siginfo.si_signo == SIGUSR1)    // сигнал о завершении программы
            {
                kill(pid, SIGTERM);
                exit(EXIT_SUCCESS);
            }
            break;
        }
    }
}

void daemon_process::setup_signal(sigset_t& sigset, siginfo_t& siginfo) noexcept
{
    sigemptyset(&sigset);                           // настраиваем сигналы которые будем обрабатывать

    sigaddset(&sigset, SIGUSR1);                    // пользовательский сигнал для завершения процесса

    sigaddset(&sigset, SIGCHLD);                    // сигнал, посылаемый при изменении статуса дочернего процесса

    sigprocmask(SIG_BLOCK, &sigset, NULL);
}