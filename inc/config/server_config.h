/**
 * Файл: server_config.h
 *
 * Описание: класс server_config реализует функционал
 *           для работы с конфигуарационным файлом сервера,
 *           класс использует паттерн singleton
 */

#ifndef _SERVER_CONFIG_H_
#define _SERVER_CONFIG_H_

#include "types.h"

#include <string>

class server_config
{
 public:

    ~server_config( );

    static server_config& get_instance() noexcept;

    void load_cfg_file( const std::string &file_name );
    const CONFIG_TYPES* get_config( ) const;

    server_config( const server_config &copy ) = delete;
    server_config& operator=( const server_config &copy ) = delete;

 private:
    const std::string get_server_name( const std::string &file_name );
    const std::string get_ip_address( const std::string &file_name );
    const unsigned int get_port( const std::string &file_name );
    const std::string get_document_root( const std::string &file_name );
    const std::string get_error_log( const std::string &file_name );
    const std::string get_access_log( const std::string &file_name );

 private:
    server_config( );

 private:
    CONFIG_TYPES *cfg_;
};
#endif //_SERVER_CONFIG_H_
