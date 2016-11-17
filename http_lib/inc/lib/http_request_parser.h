#ifndef _HTTP_REQUEST_PARSER_H_
#define _HTTP_REQUEST_PARSER_H_

#include "http_struct.h"
#include "http_request.h"

#include <string>

class http_request_parser
{
public:
    enum class parser_state
    {
        request_method_begin = 0,
        request_method,
        request_uri_begin,
        request_uri,
        request_http_version_h,
        request_http_version_ht,
        request_http_version_http,
        request_http_version_separator
    };

    enum class request_parse_result
    {
        COMPLETE,   // успешно
        INCOMPLETE, // неуспешно
        ERROR       // ошибка
    };

public:
    http_request_parser();

    ~http_request_parser() = default;

    request_parse_result parse( const std::string& src_request, http_request& request );

    http_request_parser( const http_request_parser& copy ) = delete;

    http_request_parser& operator=( const http_request_parser& copy ) = delete;

    http_request_parser( http_request_parser&& other ) = default;

    http_request_parser& operator=( http_request_parser&& other ) = default;

private:

    /**
     *  @brief начала парсинга HTTP метода
     *
     *  @param текущий символ из запроса
     *  @param структра для результата разбора
     *
     *  @return результат парсинга
     */
    http_request_parser::request_parse_result parse_request_method_begin( const char& c, http_request& request ) noexcept;

    /**
     *  @brief парсинга HTTP метода
     *
     *  @param текущий символ из запроса
     *  @param структра для результата разбора
     *
     *  @return результат парсинга
     */
    http_request_parser::request_parse_result parse_request_method( const char& c, http_request& request ) noexcept;

    /**
     *  @brief начало парсинга URI
     *
     *  @param текущий символ из запроса
     *  @param структра для результата разбора
     *
     *  @return результат парсинга
     */
    http_request_parser::request_parse_result parse_request_uri_begin( const char& c, http_request& request ) noexcept;

    http_request_parser::request_parse_result parse_request_uri( const char& c, http_request& request ) noexcept;

    /**
     * @brief метод для проверки, является ли символ из HTTP запроса допустимым ASCII кодом
     *
     * @param c символ для проверки
     *
     * @return true если смвол дявляется допустимым, false - иначе
     */
    bool is_valid_ASCII_char( const char& c ) const noexcept;

    /**
     * @brief метод для проверки, является ли символ из HTTP запроса допустимым символом
     *
     * @param c символ для проверки
     *
     * @return true если смвол дявляется допустимым, false - иначе
     */
    bool is_valid_HTTP_char( const char& c ) const noexcept;

    /**
     * @brief метод для проверки, является ли символ из HTTP запроса специальным символом
     *
     * @param c символ для проверки
     *
     * @return true если смвол дявляется допустимым, false - иначе
     */
    bool is_special_char( const char& c ) const noexcept;

private:
    parser_state state_;
};

#endif //_HTTP_REQIEST_H_