/**
 *  Файл: error_loader.h
 *
 *  Описание:
 */

#ifndef _ERROR_LOG_H_
#define _ERROR_LOG_H_

#include "server_log.h"

class error_log : public server_log
{
 public:

    ~error_log( ) { }

    static error_log& get_instance() noexcept;
    void create_log_file( const std::string &dir ) override;
    void write_log( const std::string &log ) override;

    error_log( const error_log& copy ) = delete;
    error_log& operator=( const error_log& copy ) = delete;
 protected:
    error_log( ) { }

 private:
    std::string dir_;
    FILE *h_file_;
};

#endif //_ERROR_LOG_H_