#include "types.h"
#include "process.h"
#include "daemon_process.h"
#include "process_creator.h"
#include "master_process_creator.h"

#include <memory>

#include <string.h>
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
        throw std::runtime_error(strerror(errno));
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
        case CHILD_PROCESS:
        {

            process->start_process();
            break;
        }

        case ERROR_PROCESS:
        {
            break;
        }

        default:
        {
            // ожидаем поступление сигнала
            sigwaitinfo(&sigset, &siginfo);

            if(siginfo.si_signo == SIGCHLD)   // если пришел сигнал от потомка
            {
                waitpid(pid, 0, WNOHANG);
                exit(0);
            }
            else if(siginfo.si_signo == SIGTERM) // если пришел сигнал о завершении программы
            {
                kill(pid, SIGKILL);
                exit(0);
            }
            else
            {
                //Обработка неизвестного сигнала
            }
            break;
        }
    }
}

void daemon_process::setup_signal(sigset_t& sigset, siginfo_t& siginfo) noexcept
{
    // настраиваем сигналы которые будем обрабатывать
    sigemptyset(&sigset);

    // сигнал запроса завершения процесса
    sigaddset(&sigset, SIGTERM);

    // сигнал посылаемый при изменении статуса дочернего процесса
    sigaddset(&sigset, SIGCHLD);

    sigprocmask(SIG_BLOCK, &sigset, NULL);
}