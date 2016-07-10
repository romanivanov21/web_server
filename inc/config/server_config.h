/**
 * Файл: server_config.h
 *
 * Описание: класс server_config реализует функционал
 *           для работы с конфигуарационным файлом сервера,
 *           класс использует паттерн singleton
 */

#ifndef _SERVER_CONFIG_H_
#define _SERVER_CONFIG_H_

#include <string>

class server_config
{
 public:
    static server_config* get_instance( );

    bool find_cfg_file( const std::string &file_name ) noexcept;
    const std::string get_server_name( );
    const std::string get_ip_address( );
    const unsigned int get_port( );
    const std::string get_document_root( );
    const std::string get_error_log( );
    const std::string get_access_log( );

    server_config( const server_config &copy ) = delete;
    server_config& operator=( const server_config &copy ) = delete;

 private:
    server_config( ) { };
    ~server_config( ) { };

 private:
    static server_config *s_cfg_;
    std::string file_name_;
};
#endif //_SERVER_CONFIG_H_
