#include "endpoint_ipv4.h"

#include <cstring>
#include <cassert>
#include <arpa/inet.h>
#include <array>

endpoint_ipv4::endpoint_ipv4( const std::string& ip_address, std::uint16_t port )
{
    assert( !ip_address.empty() );
    assert( ( port > 0 ) && ( port <= 65000 ) );

    std::memset( &sock_address4_, 0x00, sizeof( sock_address4_ ) );
    sock_address4_.sin_family = AF_INET;
    sock_address4_.sin_addr.s_addr = inet_addr( ip_address.c_str() );
    sock_address4_.sin_port = htons( port );
}

endpoint_ipv4::endpoint_ipv4()
{
    std::memset( &sock_address4_, 0x00, sizeof( sock_address4_ ) );
}

std::string endpoint_ipv4::get_ip_address() noexcept
{
    std::array<char, INET_ADDRSTRLEN + 1> temp_buff;
    temp_buff[INET_ADDRSTRLEN] = '\0';
    std::memset( temp_buff.data(), 0x00, INET_ADDRSTRLEN );
    inet_ntop( AF_INET, &sock_address4_.sin_addr, temp_buff.data(), INET_ADDRSTRLEN );
    return std::string( temp_buff.data() );
}

std::uint16_t endpoint_ipv4::get_port() noexcept
{
    uint16_t res = 0;
    res = htons( sock_address4_.sin_port );
    return res;
}

int endpoint_ipv4::get_domain() noexcept
{
    return AF_INET;
}

int endpoint_ipv4::get_type() noexcept
{
    return SOCK_STREAM;
}

int endpoint_ipv4::get_protocol() noexcept
{
    return IPPROTO_TCP;
}

struct sockaddr* endpoint_ipv4::get_sockaddr() noexcept
{
    return ( struct sockaddr* )&sock_address4_;
}

endpoint_ipv4::endpoint_ipv4( const endpoint_ipv4 &copy )
{
    memcpy( &sock_address4_, &copy.sock_address4_, sizeof( sock_address4_ ) );
}

socklen_t endpoint_ipv4::get_sockaddr_size() noexcept
{
    return sizeof( struct sockaddr_in );
}

int endpoint_ipv4::get_backlong() noexcept
{
    return SOMAXCONN;
}