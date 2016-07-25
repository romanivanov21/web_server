#ifndef _DAEMON_H_
#define _DAEMON_H_

#include "process_creator.h"
#include "process.h"


#include <string>

class daemon
{
public:
    daemon();
    ~daemon();

    static void init_config();
    static void init_access_log();
    static void init_error_log();

    void start_daemon();


private:
    void write_pid( pid_t pid ) const;
    void sighandler( int signum );
    void print_to_console( const std::string& msg) const;
};

#endif //_DAEMON_H_