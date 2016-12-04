/**
 *  Файл: http_request.h
 *
 *  Описание: описание структуры http запроса
 */

#ifndef _HTTP_REQUEST_H_
#define _HTTP_REQUEST_H_

#include <unordered_map>
#include <string>

struct http_request
{
    http_request()
      : method_( "" ), uri_( "" ), version_major_( 0 ), version_minor_( 0 ), headers_( 0 ),
        keep_alive_( false ) { }

    std::string method_;                                   // HTTP метод
    std::string uri_;                                      // URI
    int version_major_;                                    // Старшее число версии HTTP протокола
    int version_minor_;                                    // Младшее число версии HTTP протокола
    std::unordered_map<std::string, std::string> headers_; // Заголовки HTTP протокола
    bool keep_alive_;                                      // Поддерживать ли постоянное соединение ( для версии меньше HTTP 1.1 )
};

#endif //_HTTP_REQUEST_H_