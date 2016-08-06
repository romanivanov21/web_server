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


private:
    daemon_tool(const daemon_tool &) = delete;
    daemon_tool & operator=(const daemon_tool &) = delete;

    void monitor_process();
    void print_to_console( const std::string& msg) const;
    void setup_signal(sigset_t & sigset, siginfo_t & siginfo);
    void write_pid(const int pid, const std::string & pid_name) const;
};

#endif //_DAEMON_H_