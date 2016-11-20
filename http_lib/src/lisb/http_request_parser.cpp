#include "http_request_parser.h"

#include <cassert>

http_request_parser::http_request_parser() : state_( parser_state::request_method_begin ), current_header_() { }

http_request_parser::request_parse_result http_request_parser::parse( const std::string &src_request, http_request &request ) noexcept
{
    assert( !src_request.empty() );

    auto result = http_request_parser::request_parse_result::COMPLETE;
    auto it = src_request.cbegin();
    while( it != src_request.cend() )
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
            case http_request_parser::parser_state::request_http_version_minor_begin:
            {
                result = parse_request_http_version_minor_begin( *it, request );
                break;
            }
            case http_request_parser::parser_state::request_http_version_minor_end:
            {
                result = parse_request_http_version_minor_end( *it, request );
                break;
            }
            case http_request_parser::parser_state::request_http_version_new_line:
            {
                result = parse_request_http_version_new_line( *it );
                break;
            }
            case http_request_parser::parser_state::request_header_begin:
            {
                result = parse_request_header_begin( *it, request );
                break;
            }
            case http_request_parser::parser_state::request_before_name_space:
            {
                result = parse_request_before_name_space( *it );
                break;
            }
            case http_request_parser::parser_state::request_header_name:
            {
                result = parse_request_header_name( *it, request );
                break;
            }
            case http_request_parser::parser_state::request_header_value:
            {
                result = parse_request_header_value( *it, request );
                break;
            }
            case http_request_parser::parser_state::request_header_new_line:
            {
                result = parse_request_header_new_line( *it );
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
        request.version_major_ = c - '0';
        state_ = http_request_parser::parser_state::request_http_version_point;
        result = http_request_parser::request_parse_result::COMPLETE;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_http_version_point( const char &c, http_request& request ) noexcept
{
    auto result = http_request_parser::request_parse_result::ERROR;
    if( c == '.' )
    {
        state_ = http_request_parser::parser_state::request_http_version_minor_begin;
        result = http_request_parser::request_parse_result::COMPLETE;
    }
    else if( is_digit( c ) )
    {
        request.version_major_ = request.version_major_ * 10 + c - '0';
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_http_version_minor_begin( const char &c, http_request& request ) noexcept
{
    auto result = http_request_parser::request_parse_result::ERROR;

    if( is_digit( c ) )
    {
        request.version_minor_ = c - '0';
        state_ = parser_state::request_http_version_minor_end;
        result = http_request_parser::request_parse_result::COMPLETE;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_http_version_minor_end( const char &c, http_request &request ) noexcept
{
    auto result = http_request_parser::request_parse_result::COMPLETE;
    if( is_digit( c ) )
    {
        request.version_minor_ = request.version_minor_ * 10 + c - '0';
    }
    else if( c == '\r' )
    {
        state_ = parser_state::request_http_version_new_line;
    }
    else
    {
        result = http_request_parser::request_parse_result::ERROR;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_http_version_new_line( const char &c ) noexcept
{
    auto result = http_request_parser::request_parse_result::ERROR;
    if( c == '\n' )
    {
        state_ = parser_state::request_header_begin;
        result = http_request_parser::request_parse_result::COMPLETE;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_header_begin( const char &c, http_request& request ) noexcept
{
    auto result = http_request_parser::request_parse_result::COMPLETE;
    if( !is_valid_ASCII_char( c ) || !is_valid_HTTP_char( c ) || is_special_char( c ) )
    {
        result = http_request_parser::request_parse_result::ERROR;
    }
    else if( c == '\r' )
    {
        //TODO
    }
    else
    {
        current_header_.name_.push_back( c );
        state_ = parser_state::request_header_name;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_header_name( const char &c, http_request &request ) noexcept
{
    auto result = http_request_parser::request_parse_result::COMPLETE;
    if( c == ':' )
    {
        state_ = parser_state::request_before_name_space;
    }
    else if ( !is_valid_ASCII_char( c ) || !is_valid_HTTP_char( c ) || is_special_char( c ) )
    {
        result = http_request_parser::request_parse_result::ERROR;
    }
    else
    {
        current_header_.name_.push_back( c );
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_before_name_space( const char &c ) noexcept
{
    auto result = http_request_parser::request_parse_result::ERROR;
    if( c == ' ' )
    {
        state_ = http_request_parser::parser_state::request_header_value;
        result = http_request_parser::request_parse_result::COMPLETE;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_header_value( const char &c, http_request &request ) noexcept
{
    auto result = http_request_parser::request_parse_result::ERROR;
    if( c == '\r' )
    {
        if( ( !current_header_.name_.empty() ) && ( !current_header_.value_.empty() ) )
        {
            std::pair<std::string, std::string> header( current_header_.name_, current_header_.value_ );
            current_header_.name_.clear();
            current_header_.value_.clear();
            request.headers_.insert( header );
            state_ = http_request_parser::parser_state::request_header_new_line;
            result = http_request_parser::request_parse_result::COMPLETE;
        }
    }
    else if( !is_valid_HTTP_char( c ) )
    {
        result = http_request_parser::request_parse_result::ERROR;
    }
    else
    {
        current_header_.value_.push_back( c );
        result = http_request_parser::request_parse_result::COMPLETE;
    }
    return result;
}

http_request_parser::request_parse_result http_request_parser::parse_request_header_new_line( const char &c ) noexcept
{
    auto result = http_request_parser::request_parse_result::ERROR;
    if( c == '\n' )
    {
        state_ = http_request_parser::parser_state::request_header_begin;
        result = http_request_parser::request_parse_result::COMPLETE;
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