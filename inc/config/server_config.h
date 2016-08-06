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
    ~server_config() = default;

    /**
     * @brief инстанцирование класса singleton
     *
     * @return ссылка на единственный экземпля класса
     */
    static server_config& get_instance() noexcept;

    /**
     * @brief загрузка и чтение конфиг файла
     * @param путь до конфиг файла
     *
     * @throw server_config_exception
     */
    void load_config_file( const std::string &file_name );

    /**
     * @brief полчение указателя на структуру c конфигом
     *
     * @return указатель на CONFIG
     */
    const CONFIG_TYPES* get_config() const noexcept;

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
    server_config() = default;

 private:
    CONFIG_TYPES cfg_;
};
#endif //_SERVER_CONFIG_H_
