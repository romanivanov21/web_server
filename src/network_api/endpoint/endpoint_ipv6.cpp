#include "endpoint_ipv6.h"

#include <cstring>
#include <cassert>
#include <arpa/inet.h>
#include <types.h>

endpoint_ipv6::endpoint_ipv6()
{
    std::memset( &sock_address6_, 0x00, sizeof( sock_address6_ ) );
}

endpoint_ipv6::endpoint_ipv6( std::uint16_t port )
{
    assert( ( port > 0 ) && ( port <= tcp_port_max ) );

    std::memset( &sock_address6_, 0x00, sizeof( sock_address6_ ) );
    sock_address6_.sin6_family = AF_INET6;
    ///!TODO: функция не реализована
    //sock_address6_.sin6_addr. = inet_addr( INADDR_ANY );
    sock_address6_.sin6_port = port;
}

endpoint_ipv6::endpoint_ipv6( const std::string& ip_address, std::uint16_t port ) : ip_address_( ip_address ), port_( port )
{
    assert( !ip_address_.empty() );
    assert( ( port_ > 0 ) && ( port_ < tcp_port_max ) );

    std::memset( &sock_address6_, 0x00, sizeof( sock_address6_ ) );
    sock_address6_.sin6_family = AF_INET6;
    ///!TODO: функция не реализована
    //sock_address6_.sin6_addr = inet_addr( INADDR_ANY );
    sock_address6_.sin6_port = port;
}

std::string endpoint_ipv6::get_ip_address() const noexcept
{
    std::string res = "";
    res.resize( INET6_ADDRSTRLEN );
    inet_ntop( AF_INET, &sock_address6_.sin6_addr, &res[0], INET6_ADDRSTRLEN );
    return res;
}

struct sockaddr* endpoint_ipv6::get_sockaddr() const noexcept
{
    ///!TODO: функция не реализована
    //sock_address6_.sin6_addr
    //sock_address6_.sin_addr.s_addr = inet_addr( ip_address_.c_str() );
    //sock_address6_.sin_port = htons( port_ );
    return ( struct sockaddr* )&sock_address6_;
}

socklen_t endpoint_ipv6::get_sockaddr_size() const noexcept
{
    return sizeof( struct sockaddr_in6 );
}

std::uint16_t endpoint_ipv6::get_port() const noexcept
{
    return port_;
}

int endpoint_ipv6::get_domain() const noexcept
{
    return AF_INET6;
}

int endpoint_ipv6::get_type() const noexcept
{
    return SOCK_STREAM;
}

int endpoint_ipv6::get_protocol() const noexcept
{
    return IPPROTO_TCP;
}

int endpoint_ipv6::get_backlong() const noexcept
{
    return SOMAXCONN;
}