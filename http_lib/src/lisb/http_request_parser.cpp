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
            case http_request_parser::parser_state::request_http_version_h:
            {
                result = parse_request_http_version_h( *it );
                break;
            }
            case http_request_parser::parser_state::request_http_version_ht:
            {
                result = parse_request_http_version_ht( *it );
                break;
            }
            case http_request_parser::parser_state::request_http_version_htt:
            {
                result = parse_request_http_version_htt( *it );
                break;
            }
            case http_request_parser::parser_state::request_http_version_http:
            {
                result = parse_request_http_version_http( *it );
                break;
            }
            case http_request_parser::parser_state::request_http_version_separator:
            {
                result = parse_request_http_version_separator( *it );
                break;
            }
            case http_request_parser::parser_state::request_http_version_major:
            {
                result = parse_request_http_version_major( *it, request );
                break;
            }
            case http_request_parser::parser_state::request_http_version_point:
            {
                result = parse_request_http_version_point( *it, request );
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

http_request_parser::request_parse_result http_request_parser::parse_request_http_version_h( const char &c ) noexcept
{
    auto result = http_request_parser::request_parse_result::ERROR;
    if( c == 'H' )
    {
        state_ = http_request_parser::parser_state::request_http_version_ht;
        result = http_request_parser::request_parse_result::COMPLETE;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_http_version_ht( const char &c ) noexcept
{
    auto result = http_request_parser::request_parse_result::ERROR;
    if( c == 'T' )
    {
        state_ = http_request_parser::parser_state::request_http_version_htt;
        result = http_request_parser::request_parse_result::COMPLETE;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_http_version_htt( const char &c ) noexcept
{
    auto result = http_request_parser::request_parse_result::ERROR;
    if( c == 'T' )
    {
        state_ = http_request_parser::parser_state::request_http_version_http;
        result = http_request_parser::request_parse_result::COMPLETE;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_http_version_http( const char &c ) noexcept
{
    auto result = http_request_parser::request_parse_result::ERROR;
    if( c == 'P' )
    {
        state_ = http_request_parser::parser_state::request_http_version_separator;
        result = http_request_parser::request_parse_result::COMPLETE;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_http_version_separator( const char &c ) noexcept
{
    auto result = http_request_parser::request_parse_result::ERROR;
    if( c == '/' )
    {
        state_ = http_request_parser::parser_state::request_http_version_major;
        result = http_request_parser::request_parse_result::COMPLETE;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_http_version_major( const char &c, http_request& request ) noexcept
{
    auto result = http_request_parser::request_parse_result::ERROR;
    if( is_digit( c ) )
    {
        request.version_major_ = std::atoi( &c );
        state_ = http_request_parser::parser_state::request_http_version_point;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_http_version_point( const char &c, http_request& request ) noexcept
{
    auto result = http_request_parser::request_parse_result::ERROR;
    if( c == '.' )
    {
        state_ = http_request_parser::parser_state::request_http_version_minor;
        result = http_request_parser::request_parse_result::COMPLETE;
    }
    else if( is_digit( c ) )
    {
        request.version_major_ = request.version_major_ * 10 + c;
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

bool http_request_parser::is_digit( const char &c ) const noexcept
{
    return ( ( c >= '0' ) && ( c <= '9' ) );
}