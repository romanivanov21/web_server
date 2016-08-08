#ifndef _DAEMON_H_
#define _DAEMON_H_

#include <string>
#include <signal.h>

class daemon_tool
{
public:
    daemon_tool();
    ~daemon_tool();

    static void init_config();
    static void init_access_log();
    static void init_error_log();

    void start_daemon();

    daemon_tool(const daemon_tool &) = delete;
    daemon_tool & operator=(const daemon_tool &) = delete;
private:
    void write_pid(const int pid, const std::string & pid_name);

};

#endif //_DAEMON_H_