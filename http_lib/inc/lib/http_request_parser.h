/**
 *  Файл: http_request_parser.h
 *
 *  Описание: Парсер запроса HTTP
 */

#ifndef _HTTP_REQUEST_PARSER_H_
#define _HTTP_REQUEST_PARSER_H_

#include "http_struct.h"
#include "http_request.h"

#include <string>

class http_request_parser
{
public:
    enum class parser_state : uint64_t
    {
        request_method_begin = 0,
        request_method,
        request_uri_begin,
        request_uri,
        request_http_version_h,
        request_http_version_ht,
        request_http_version_htt,
        request_http_version_http,
        request_http_version_separator,
        request_http_version_major,
        request_http_version_point,
        request_http_version_minor_begin,
        request_http_version_minor_end,
        request_http_version_new_line,
        request_header_begin,
        request_header_name,
        request_before_name_space,
        request_header_value
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

    request_parse_result parse( const std::string& src_request, http_request& request ) noexcept;

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

    /**
     *  @brief парсинг URI
     */
    http_request_parser::request_parse_result parse_request_uri( const char& c, http_request& request ) noexcept;

    http_request_parser::request_parse_result parse_request_http_version_h( const char& c ) noexcept;

    http_request_parser::request_parse_result parse_request_http_version_ht( const char& c ) noexcept;

    http_request_parser::request_parse_result parse_request_http_version_htt( const char& c ) noexcept;

    http_request_parser::request_parse_result parse_request_http_version_http( const char& c ) noexcept;

    http_request_parser::request_parse_result parse_request_http_version_separator( const char& c ) noexcept;

    http_request_parser::request_parse_result parse_request_http_version_major( const char& c, http_request& request ) noexcept;

    http_request_parser::request_parse_result parse_request_http_version_point( const char& c, http_request& request) noexcept;

    http_request_parser::request_parse_result parse_request_http_version_minor_begin( const char& c, http_request& request ) noexcept;

    http_request_parser::request_parse_result parse_request_http_version_minor_end( const char& c, http_request& request ) noexcept;

    http_request_parser::request_parse_result parse_request_http_version_new_line( const char& c ) noexcept;

    http_request_parser::request_parse_result parse_request_header_begin( const char& c, http_request& request ) noexcept;

    http_request_parser::request_parse_result parse_request_header_name( const char& c, http_request& request ) noexcept;

    http_request_parser::request_parse_result parse_request_before_name_space( const char& c ) noexcept;

    http_request_parser::request_parse_result parse_request_header_value( const char& c, http_request& request )noexcept;

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
     * @param символ для проверки
     *
     * @return true если символ дявляется допустимым, false - иначе
     */
    bool is_special_char( const char& c ) const noexcept;

    /**
     * @break проверка, является ли симовл числом
     *
     * @param символ для проверки
     *
     * @return true если символ явялется числом, false - иначе
     */
    bool is_digit( const char& c ) const noexcept;
private:
    struct header
    {
        header() : name_( "" ), value_( "" ) { }

        std::string name_;
        std::string value_;
    };

private:
    parser_state state_;
    header current_header_;
};

#endif //_HTTP_REQIEST_H_