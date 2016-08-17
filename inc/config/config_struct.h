/**
 *  Файл: config_struct.h
 *
 *  Описание: Структура, содержащий инфломации из конфиг файла
 *
 */

#ifndef _CONFIG_STRUCT_H_
#define _CONFIG_STRUCT_H_

#include <string>

/* Структра для харнения основную конфигурацию сервера */
struct config_server
{
    /* Структра для хранения инцормации о сетевом соединении */
    struct server_connection
    {
        size_t ip_version_;             // версия ip адреса
        std::string ip_address_;        // ip адрес
        size_t listen_;                 // порт, на котором принимаются входящие соединение
    };

    /* Структра для хранения основных диркторий сервера */
    struct server_directories
    {
        std::string document_root_;     // корневая директория сервера
    };

    /* Струтра для хранения информации о лог файлах */
    struct server_logs
    {
        std::string error_log_;         // директория до файла логирования ошибок
        std::string access_log_;        // директория до файла логирования выполненных действий
    };

    std::string name_;                  // доменное имя сервера
    server_connection connection_;
    server_directories directories_;
    server_logs logs_;
};

/* Структра для хранения конфигураций дополнительных модулей сервера */
struct config_modules
{
    std::string mod_CGI_;
};

/* Основная структрадля хранения информации из конфигурационного файла сервера */
struct config_struct
{
    config_server server_;              // конфигурация сервера
    config_modules modules_;            // конфигурация дополниельных модулей
};

#endif //_CONFIG_STRUCT_H_