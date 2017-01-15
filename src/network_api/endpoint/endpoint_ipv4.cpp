#include "endpoint_ipv4.h"

#include <cstring>
#include <cassert>
#include <arpa/inet.h>
#include <array>
#include <types.h>

endpoint_ipv4::endpoint_ipv4()
{
    std::memset( &sock_address4_, 0x00, sizeof( sock_address4_ ) );
}

endpoint_ipv4::endpoint_ipv4( const std::string& ip_address, std::uint16_t port )
{
    assert( !ip_address.empty() );
    assert( ( port > 0 ) && ( port <= tcp_port_max ) );

    std::memset( &sock_address4_, 0x00, sizeof( sock_address4_ ) );
    sock_address4_.sin_family = AF_INET;
    sock_address4_.sin_addr.s_addr = inet_addr( ip_address.c_str() );
    sock_address4_.sin_port = htons( port );
}

endpoint_ipv4::endpoint_ipv4( std::uint16_t port )
{
    assert( ( port > 0 ) && ( port <= tcp_port_max ) );

    std::memset( &sock_address4_, 0x00, sizeof( sock_address4_ ) );
    sock_address4_.sin_family = AF_INET;
    sock_address4_.sin_addr.s_addr = inet_addr( INADDR_ANY );
    sock_address4_.sin_port = port;
}

std::string endpoint_ipv4::get_ip_address() const noexcept
{
    std::array<char, INET_ADDRSTRLEN + 1> temp_buff;
    temp_buff[INET_ADDRSTRLEN] = '\0';
    std::memset( temp_buff.data(), 0x00, INET_ADDRSTRLEN );
    inet_ntop( AF_INET, &sock_address4_.sin_addr, temp_buff.data(), INET_ADDRSTRLEN );
    return std::string( temp_buff.data() );
}

std::uint16_t endpoint_ipv4::get_port() const noexcept
{
    uint16_t res = 0;
    res = htons( sock_address4_.sin_port );
    return res;
}

int endpoint_ipv4::get_domain() const noexcept
{
    return AF_INET;
}

int endpoint_ipv4::get_type() const noexcept
{
    return SOCK_STREAM;
}

int endpoint_ipv4::get_protocol() const noexcept
{
    return IPPROTO_TCP;
}

struct sockaddr* endpoint_ipv4::get_sockaddr() const noexcept
{
    return ( struct sockaddr* )&sock_address4_;
}

endpoint_ipv4::endpoint_ipv4( const endpoint_ipv4 &copy )
{
    std::memcpy( &sock_address4_, &copy.sock_address4_, sizeof( sock_address4_ ) );
}

endpoint_ipv4& endpoint_ipv4::operator=( const endpoint_ipv4 &copy )
{
    if( this != &copy )
    {
        std::memcpy( &sock_address4_, &copy.sock_address4_, sizeof( sock_address4_ ) );
    }
    return *this;
}

endpoint_ipv4::endpoint_ipv4( endpoint_ipv4&& other )
{
    std::memcpy( &sock_address4_, &other.sock_address4_, sizeof( sock_address4_ ) );
    std::memset( &other.sock_address4_, 0x00, sizeof( other.sock_address4_ ) );
}

endpoint_ipv4& endpoint_ipv4::operator=( endpoint_ipv4&& other )
{
    std::swap( sock_address4_, other.sock_address4_ );
    return *this;
}

socklen_t endpoint_ipv4::get_sockaddr_size() const noexcept
{
    return sizeof( struct sockaddr_in );
}

int endpoint_ipv4::get_backlong() const noexcept
{
    return SOMAXCONN;
}