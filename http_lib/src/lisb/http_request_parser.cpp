#include "http_request_parser.h"

#include <cassert>

http_request_parser::http_request_parser() : state_( parser_state::start ) { }

http_request_parser::request_parse_result http_request_parser::parse( const std::string &src_request, http_request &request )
{
    assert( !src_request.empty() );

    http_request_parser::request_parse_result result = http_request_parser::request_parse_result::COMPLETE;

    auto it = src_request.begin();
    while( it != src_request.end() )
    {
        switch( state_ )
        {
            case http_request_parser::parser_state::start:
            {
                result = parse_state_start( *it, request );
                break;
            }
            case http_request_parser::parser_state::request_method:
            {
                result = parse_state_request_method( *it, request );
                break;
            }
            case http_request_parser::parser_state::request_uri_begin:
            {
                break;
            }
        }

        if( ( result == http_request_parser::request_parse_result::ERROR )
            || ( result == http_request_parser::request_parse_result::INCOMPLETE ) )
        {
            break;
        }
        ++it;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_state_start( const char& c, http_request& request )
{
    http_request_parser::request_parse_result result = http_request_parser::request_parse_result::ERROR;
    if( ( is_valid_ASCII_char( c ) ) || ( is_valid_HTTP_char( c ) || ( !is_special_char( c ) ) ) )
    {
        request.method_.push_back( c );
        state_ = http_request_parser::parser_state::request_method;
        result = http_request_parser::request_parse_result::COMPLETE;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_state_request_method( const char &c, http_request &request )
{
    http_request_parser::request_parse_result result = http_request_parser::request_parse_result::COMPLETE;
    if( c == ' ' )
    {
        state_ = http_request_parser::parser_state::request_uri_begin;
    }
    else if( ( !is_valid_ASCII_char( c ) ) || ( !is_valid_HTTP_char( c ) ) || ( is_special_char( c ) ) )
    {
        result = http_request_parser::request_parse_result::ERROR;
    }
    else
    {
        request.method_.push_back( c );
    }
    return result;
}

bool http_request_parser::is_valid_ASCII_char( const char& c ) const noexcept
{
    return ( ( c >= 0 ) && ( c <= 127 ) );
}

bool http_request_parser::is_valid_HTTP_char( const char &c ) const noexcept
{
    return ( !( ( c >= 0 ) && ( c <= 31 ) ) || ( c != 127 ) );
}

bool http_request_parser::is_special_char( const char &c ) const noexcept
{
    switch ( c )
    {
        case '(': case ')': case '<': case '>': case '@':
        case ',': case ';': case ':': case '\\': case '"':
        case '/': case '[': case ']': case '?': case '=':
        case '{': case '}': case ' ': case '\t':
            return true;
        default:
            return false;
    }
}