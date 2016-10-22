#include "types.h"
#include "process.h"
#include "daemon_process.h"
#include "process_creator.h"
#include "master_process_creator.h"
#include "access_log.h"
#include "error_log.h"

#include <memory>
#include <unistd.h>
#include <sys/wait.h>

void daemon_process::start_process() noexcept
{
    sigset_t sigset;
    siginfo_t siginfo;

    pid_t sid = setsid();
    if( sid != default_error_code )
    {

        chdir( "/" );

        close( STDIN_FILENO );
        close( STDOUT_FILENO );
        close( STDERR_FILENO );

        setup_signal( sigset,siginfo );

        std::unique_ptr<process_creator> process_creator = std::make_unique<master_process_creator>();
        std::unique_ptr<process> process( process_creator->get_process());

        pid_t pid = process_creator->create_process();

        switch( pid )
        {
            case process_creator::CHILD_PROCESS:
            {
                access_log::get_instance()->save_log( "Master process was created" );
                process->start_process();
                break;
            }

            case process_creator::ERROR_PROCESS:
            {
                error_log::get_instance()->save_log( "Error create master process" );
                break;
            }

            default:
            {
                access_log::get_instance()->save_log( "wait signal" );
                // ожидаем поступление сигнала
                sigwaitinfo( &sigset, &siginfo );
                access_log::get_instance()->save_log( "wait signal1" );

                if( siginfo.si_signo == SIGCHLD )   // если пришел сигнал от потомка
                {
                    access_log::get_instance()->save_log( "exit daemon" );
                    waitpid( pid, 0, WNOHANG );
                    exit( 0 );
                }
                else if( siginfo.si_signo == SIGTERM ) // если пришел сигнал о завершении программы
                {
                    access_log::get_instance()->save_log( "exit daemon1" );
                    kill( pid, SIGKILL );
                    exit( 0 );
                }
                break;
            }
        }
    }
    else
    {
        error_log::get_instance()->save_log( "set sid error" );
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