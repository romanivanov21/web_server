#ifndef _ERROR_LOG_H_
#define _ERROR_LOG_H_

#include "server_log.h"

class error_log : public server_log
{
private:
    FILE * h_file_;
    std::string dir_;

    error_log();
    ~error_log();

    static error_log * log;

public:
    static error_log * get_instance() noexcept;

    void set_log_dir(const std::string & dir) override;
    void create_log_file(void) const override;
    void open_log_file(void) override;
    void write_to_log_file(const std::string & msg) const override;
    void close_log_file(void) override;

    error_log(const error_log & copy) = delete;
    error_log & operator=(const error_log & copy) = delete;
};

#endif //_ERROR_LOG_H_