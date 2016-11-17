#include "http_request_parser.h"

#include <cassert>

http_request_parser::http_request_parser() : state_( parser_state::request_method_begin ) { }

http_request_parser::request_parse_result http_request_parser::parse( const std::string &src_request, http_request &request )
{
    assert( !src_request.empty() );

    auto result = http_request_parser::request_parse_result::COMPLETE;
    auto it = src_request.begin();
    while( it != src_request.end() )
    {
        switch( state_ )
        {
            case http_request_parser::parser_state::request_method_begin:
            {
                result = parse_request_method_begin( *it, request );
                break;
            }
            case http_request_parser::parser_state::request_method:
            {
                result = parse_request_method( *it, request );
                break;
            }
            case http_request_parser::parser_state::request_uri_begin:
            {
                result = parse_request_uri_begin( *it, request );
                break;
            }
            case http_request_parser::parser_state::request_uri:
            {
                result = parse_request_uri( *it, request );
                break;
            }
            default:
            {
                result = http_request_parser::request_parse_result::INCOMPLETE;
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

http_request_parser::request_parse_result http_request_parser::parse_request_method_begin( const char& c, http_request& request ) noexcept
{
    auto result = http_request_parser::request_parse_result::ERROR;
    if( ( is_valid_ASCII_char( c ) ) || ( is_valid_HTTP_char( c ) || ( !is_special_char( c ) ) ) )
    {
        request.method_.push_back( c );
        state_ = http_request_parser::parser_state::request_method;
        result = http_request_parser::request_parse_result::COMPLETE;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_method( const char &c, http_request &request ) noexcept
{
    auto result = http_request_parser::request_parse_result::COMPLETE;
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

http_request_parser::request_parse_result http_request_parser::parse_request_uri_begin( const char &c, http_request& request ) noexcept
{
    auto result = http_request_parser::request_parse_result::ERROR;
    if( is_valid_HTTP_char( c ) )
    {
        request.uri_.push_back( c );
        state_ = http_request_parser::parser_state::request_uri;
        result = http_request_parser::request_parse_result::COMPLETE;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_uri( const char &c, http_request &request ) noexcept
{
    auto result = http_request_parser::request_parse_result::COMPLETE;
    if( c == ' ' )
    {
        state_ = http_request_parser::parser_state::request_http_version_h;
    }
    else if( is_special_char( c ) )
    {
        result = http_request_parser::request_parse_result::ERROR;
    }
    else if( c == '\r' )
    {
        request.version_major_ = 0;
        request.version_major_ = 0;
    }
    else
    {
        request.uri_.push_back( c );
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