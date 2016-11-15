#include "http_request_parser.h"

#include <cassert>

http_request_parser::http_request_parser() : state_( parser_state::method_start ) { }

request_parse_result http_request_parser::parse( const std::string &src_request, http_request &request )
{
    assert( !src_request.empty() );
}