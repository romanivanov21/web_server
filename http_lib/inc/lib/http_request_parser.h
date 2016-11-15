#ifndef _HTTP_REQUEST_PARSER_H_
#define _HTTP_REQUEST_PARSER_H_

#include "http_struct.h"
#include "http_request.h"

#include <string>

class http_request_parser
{
public:
    http_request_parser();

    ~http_request_parser() = default;

    request_parse_result parse( const std::string& src_request, http_request& request );

    http_request_parser( const http_request_parser& copy ) = delete;

    http_request_parser& operator=( const http_request_parser& copy ) = delete;

    enum class parser_state
    {
        method_start = 0
    };

private:
    parser_state state_;
};

#endif //_HTTP_REQIEST_H_