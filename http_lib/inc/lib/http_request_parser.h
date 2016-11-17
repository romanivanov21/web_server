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
        start = 0,
        request_method,
        request_uri_begin
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

    http_request_parser::request_parse_result parse_state_start( const char& c, http_request& request );

    http_request_parser::request_parse_result parse_state_request_method( const char& c, http_request& request );
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