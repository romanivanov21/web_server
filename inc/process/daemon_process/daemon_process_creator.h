#ifndef _DAEMON_PROCESS_CREATOR_H_
#define _DAEMON_PROCESS_CREATOR_H_

#include "process_creator.h"

class daemon_process_creator : public process_creator
{
public:
    daemon_process_creator();
    ~daemon_process_creator();

    pid_t create_process() noexcept override;
    process * get_process() noexcept override;


    daemon_process_creator(const daemon_process_creator & copy) = delete;
    daemon_process_creator & operator=(const daemon_process_creator & copy) = delete;
};

#endif //_DAEMON_PROCESS_CREATOR_H_