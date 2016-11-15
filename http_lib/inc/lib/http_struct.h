/**
 *  Файл: http_struct.h
 *
 *  Описание: струтуры реализации HTTP протокола ( см. rfc2616 )
 */

#ifndef _HTTP_STRUCT_H_
#define _HTTP_STRUCT_H_

#include <string>

enum class request_parse_result
{
    COMPLETE,   // успешно
    INCOMPLETE, // неуспешно
    ERROR       // ошибка
};

/* Методы HTTP запроса */
enum class http_methods : u_int8_t
{
    OPTIONS,
    GET,
    HEAD, //заголовки без контента
    POST,
    PUT,
    DELETE,
    TRACE,
    CONNECT
};

/* Статурс HTTP запроса */
enum class status_codes : u_int16_t
{
    /* Informational 1xx */
    CONTITNUE_100 = 100,
    SWITHING_PROTOCOLS_101 = 101,

    /* Successful 2xx*/
    OK_200 = 200,
    CREATED_201 = 201,
    ACCEPTED_202 = 202,
    NOT_AUTHORATIVE_203 = 203,
    NO_CONTENT_204 = 204,
    RESET_CONTENTS_205 = 205,
    PARTIAL_CONTENT_206 = 206,

    /*  Redirection 3xx */
    MULTIPLE_CHOICES_300 = 300,
    MOVED_PERMANENTLY_301 = 301,
    FOUND_302 = 302,
    SEE_OTHER_303 = 303,
    NOT_MODIFIED_304 = 304,
    USE_PROXY_305 = 305,
    UNUSED_306 = 306,
    TEMPORARY_REDIRECT_307 = 307,

    /* Client error 4xx */
    BAD_REAUET_400 = 400,
    UNAUTHORIZED_401 = 401,
    PYMENT_REQUIRED_402 = 402,
    FORBIDDER_403 = 403,
    NOT_FOUND_404 = 404,
    METHOD_NOT_ALLOWED_405 = 405,
    NOT_ACCEPTABLE_406 = 406,
    ROXY_AUTHENTICATION_REQUIRED_407 = 407,
    REQUSET_TIMEOUT_408 = 408,
    CONFLICT_409 = 409,
    GONE_410 = 410,
    LENGTH_REQUORED_411 = 411,
    PRECONDITION_FAILED_412 = 412,
    REQUEST_ENTRY_TOO_LARGE_413 = 413,
    REQUEST_URI_TOO_LONG_414 = 414,
    UNSUPPORTED_MEDIA_TYPE_415 = 415,
    REQUESTED_RENGE_NOT_SATISFAIBLE_416 = 416,
    EXPACTATION_FAILED_417 = 417,

    /* Server error 5xx */
    INTERNAL_SERVER_ERROR_500 = 500,
    NOT_IMPLEMENTED_501 = 501,
    BAD_GATWAY_502 = 502,
    SERVICE_UNAVAIBLE_503 = 503,
    GATWAI_TIMEOUT_504 = 504,
    HTTP_VERSION_NOT_SUPPORTED_505 = 505
};

enum class http_server_heders
{
    Date,
    Server,
    LastModifiend,
    AcceptRanges,
    Etag,
    ContentLength,
    ContentType,
    CacheControl,
    SetCookie
};

enum class http_version { HTTP_1_0, HTTP_1_1 };

#endif //_HTTP_STRUCT_H_