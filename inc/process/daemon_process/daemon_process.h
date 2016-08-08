#ifndef _DAEMON_PROCESS_H_
#define _DAEMON_PROCESS_H_

#include "process.h"

#include <signal.h>

class daemon_process : public process
{
private:
    void setup_signal(sigset_t & sigset, siginfo_t & siginfo);

public:
    daemon_process() {};
    ~daemon_process() {};

    void start_process() override;

    daemon_process(const daemon_process & copy) = delete;
    daemon_process & operator=(const daemon_process & copy) = delete;
};

#endif //_DAEMON_PROCESS_H_