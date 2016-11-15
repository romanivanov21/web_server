#include "http_request_parser.h"

#include <cassert>

http_request_parser::http_request_parser() : state_( parser_state::method_start ) { }

http_request_parser::request_parse_result http_request_parser::parse( const std::string &src_request, http_request &request )
{
    assert( !src_request.empty() );
}