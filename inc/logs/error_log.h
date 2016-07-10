/**
 *  Файл: error_loader.h
 *
 *  Описание:
 */

#ifndef _ERROR_LOG_H_
#define _ERROR_LOG_H_

#include <string>

class error_log
{
 public:
    error_log* get_instance( );
    void set_dir( std::string dir );
    std::string get_dir( ) const noexcept;

    void create_log_file( );
    void write( const std::string &str );

    error_log( const error_log& copy ) = delete;
    error_log& operator=( const error_log& copy ) = delete;
 private:
    error_log( ) { }
    ~error_log( ) { }

    std::string dir_;
    static error_log* err_log_;
};

#endif //_ERROR_LOG_H_