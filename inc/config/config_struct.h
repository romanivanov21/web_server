/**
 *  Файл: config_struct.h
 *
 *  Описание: Структура, содержащий инфломации из конфиг файла
 *
 */

#ifndef _CONFIG_STRUCT_H_
#define _CONFIG_STRUCT_H_

#ifdef _DEBUG
#include <iostream>
#endif //_DEBUG

#ifdef __linux__
#include <netinet/in.h>
#include <arpa/inet.h>
#endif //__linux__

#include <string>
#include <vector>

/* Структра для харнения основную конфигурацию сервера */
struct config_server
{
    /* Структра для хранения инцормации о сетевом соединении */
    struct server_connection
    {
        /* Перечисление для опеределения валидности конфигурации ip_version */
        enum ip_version_type { CONFIG_IPv4 = 4, CONFIG_IPv6 = 6 };

        static bool is_valid_ip_address( const std::string& ip_address, ip_version_type version_type )
        {
            bool res = false;
            struct sockaddr_in sa;
            if( version_type == ip_version_type::CONFIG_IPv4 )
            {
                res = ( ( inet_pton(AF_INET, ip_address.c_str(), &(sa.sin_addr) ) ) != 0 );
            }
            else if( version_type == ip_version_type::CONFIG_IPv6 )
            {
                res = ( ( inet_pton(AF_INET6, ip_address.c_str(), &(sa.sin_addr) ) ) != 0 );
            }
            return res;
        }

        ip_version_type ip_version_;      // версия ip адреса
        std::string ip_address_;          // ip адрес
        size_t listen_;                   // порт, на котором принимаются входящие соединение
    };

    /* Структра для хранения основных диркторий сервера */
    struct server_directories
    {
        std::string document_root_;       // корневая директория сервера
    };

    /* Струтра для хранения информации о лог файлах */
    struct server_logs
    {
        std::string error_log_;           // директория до файла логирования ошибок
        std::string access_log_;          // директория до файла логирования выполненных действий
    };

    std::string name_;                    // доменное имя сервера
    server_connection connection_;
    server_directories directories_;
    server_logs logs_;
};

/* Структра для хранения конфигураций дополнительных модулей сервера */
struct config_modules
{
    std::map<std::string, std::string> mod_; // информация о дополнительных модулях ( имя и директория конфиг файла)
};

/* Основная структрадля хранения информации из конфигурационного файла сервера */
struct config_struct
{
    #ifdef _DEBUG
    void print_to_console() const noexcept
    {
        std::cout<<"Name: " + server_.name_<<std::endl;
        std::cout<<"ip_version: " + std::to_string( server_.connection_.ip_version_ )<<std::endl;
        std::cout<<"ip_address: " + server_.connection_.ip_address_<<std::endl;
        std::cout<<"listen: " + std::to_string( server_.connection_.listen_ )<<std::endl;
        std::cout<<"document_root: " + server_.directories_.document_root_<<std::endl;
        std::cout<<"access_log: " + server_.logs_.access_log_<<std::endl;
        std::cout<<"error_log: " + server_.logs_.error_log_<<std::endl;
        for( auto item : modules_.mod_ )
        {
            std::cout<<item.first + ": " + item.second<<std::endl;
        }
    }
    #endif //_DEBUG

    config_server server_;                // конфигурация сервера
    config_modules modules_;              // конфигурация дополниельных модулей
};

#endif //_CONFIG_STRUCT_H_