#ifndef _SERVER_LOG_H_
#define _SERVER_LOG_H_

#include <string>

class server_log
{
 public:
    server_log() { }
    virtual ~server_log() { }

    virtual void create_log_file( const std::string &dir ) = 0;
    virtual void write_log( const std::string &log ) = 0;

    server_log( const server_log &copy ) = delete;
    server_log& operator=( const server_log &copy ) = delete;
};

#endif //_SERVER_LOG_H_