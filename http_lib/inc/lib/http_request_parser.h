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
    /* Перечисление с сотояниями HTTP парсера */
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
        request_header_value,
        request_header_new_line,
        request_parse_end
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

    /**
     *  @brief парсер http запроса
     *
     *  @param src_request строка запроса
     *  @param request структура, для заполнения реузльтат разбора HTTP запроса
     *
     *  @return результат парсинга
     */
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
     *  @param c текущий символ из запроса
     *  @param request структра для результата разбора
     *
     *  @return результат парсинга
     */
    http_request_parser::request_parse_result parse_request_uri_begin( const char& c, http_request& request ) noexcept;

    /**
     *  @brief парсинг URI
     *
     *  @param c текущий символ из запроса
     *  @param request структра для результата разбора
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_uri( const char& c, http_request& request ) noexcept;

    /**
     *  @brief разбор версии HTTP протокола ( определение H )
     *
     *  @param c текущий символ из запроса
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_http_version_h( const char& c ) noexcept;

    /**
     *  @brief разбор версии HTTP протокола ( определение HT )
     *
     *  @param c текущий символ из запроса
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_http_version_ht( const char& c ) noexcept;

    /**
     *  @brief разбор версии HTTP протокола ( определение HTT )
     *
     *  @param c текущий символ из запроса
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_http_version_htt( const char& c ) noexcept;

    /**
     *  @brief разбор версии HTTP протокола ( определение HTTP )
     *
     *  @param c текущий символ из запроса
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_http_version_http( const char& c ) noexcept;

    /**
     *  @brief разбор версии HTTP протокола ( определение разделителя HTTP/ )
     *
     *  @param c текущий символ из запроса
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_http_version_separator( const char& c ) noexcept;

    /**
     *  @brief разбор версии HTTP протокола ( определение старшой версии HTTP/1 )
     *
     *  @param c текущий символ из запроса
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_http_version_major( const char& c, http_request& request ) noexcept;

    /**
     *  @brief разбор версии HTTP протокола ( определение точки разделяющее старшее и младшее значение версии HTTP/1. )
     *
     *  @param c текущий символ из запроса
     *  @param request структура для результата разбора
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_http_version_point( const char& c, http_request& request) noexcept;

    /**
     *  @brief разбор версии HTTP протокола ( определение младшего значения версии HTTP/1.1 )
     *
     *  @param c текущий символ из запроса
     *  @param request структура для результата разбора
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_http_version_minor_begin( const char& c, http_request& request ) noexcept;

    /**
     *  @brief разбор версии HTTP протокола ( завершение разбора версии HTTP потокола )
     *
     *  @param c текущий символ из запроса
     *  @param request структура для результата разбора
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_http_version_minor_end( const char& c, http_request& request ) noexcept;

    /**
     *  @brief разбор перехода на новую строку
     *
     *  @param c текущий символ из запроса
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_http_version_new_line( const char& c ) noexcept;

    /**
     *  @brief начало разбора заголовка HTTP
     *
     *  @param c текущий символ из запроса
     *  @param request структура для результата разбора
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_header_begin( const char& c, http_request& request ) noexcept;

    /**
     *  @brief разбор имени заголовка HTTP
     *
     *  @param c текущий символ из запроса
     *  @param request структура для результата разбора
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_header_name( const char& c, http_request& request ) noexcept;

    /**
     *  @brief разбор разделителя ( проблел ) между именем заголовка и его значенимем
     *
     *  @param c текущий символ из запроса
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_before_name_space( const char& c ) noexcept;

    /**
     *  @brief разбор значения заголовка HTTP протокола
     *
     *  @param c текущий символ из запроса
     *  @param request структура для результата разбора
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_header_value( const char& c, http_request& request )noexcept;

    /**
     *  @brief определение новой строки /r/n
     *
     *  @param c текущий символ из запроса
     *
     *  @return реузльтат парсинга
     */
    http_request_parser::request_parse_result parse_request_header_new_line( const char& c ) noexcept;

    /**
    *  @brief определение второго /r/n и завершение парсинга запроса
    *
    *  @param c текущий символ из запроса
    *
    *  @return реузльтат парсинга
    */
    http_request_parser::request_parse_result parse_request_end( const char& c ) noexcept;

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

        std::string name_;   // заголовок HTTP
        std::string value_;  // значение
    };

private:
    parser_state state_;    // текущее состояние парсера
    header current_header_; // текущий заполняемый HTTP заголовок ( при разборе HTTP заголовка сначала заполняется поле
                            // current_header_, затем записывается в хэш-таблицу из структуры http_request )
};

#endif //_HTTP_REQIEST_H_