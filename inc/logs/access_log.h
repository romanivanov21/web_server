#ifndef _ACCESS_LOG_H_
#define _ACCESS_LOG_H_

#include "server_log.h"

class access_log : public server_log
{
private:
    FILE * h_file_;
    std::string dir_;

    access_log();
    ~access_log();

    static access_log * log;

public:
    static access_log * get_instance() noexcept;

    void set_log_dir(const std::string & dir) override;
    void create_log_file(void) const override;
    void open_log_file(void) override;
    void write_to_log_file(const std::string & msg) const override;
    void close_log_file(void) override;

    access_log(const access_log & copy) = delete;
    access_log & operator=(const access_log & copy) = delete;
};

#endif //_ACCESS_LOG_H_