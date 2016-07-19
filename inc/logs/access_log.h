/**
 *  Файл: access_error.h
 *
 *  Описание:
 */

#include "server_log.h"

class access_log : public server_log
{
 public:
    ~access_log( ) { }

    static access_log& get_instance( ) noexcept;
    void create_log_file( const std::string &dir ) override;
    void write_log( const std::string &log ) override;

    access_log( const access_log &copy ) = delete;
    access_log& operator=( const access_log &copy ) = delete;
 protected:
    access_log( ) { }

 private:
    std::string dir_;
    FILE *h_file_;
};