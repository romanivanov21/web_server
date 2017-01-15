#ifndef _ENDPOINT_IPV4_H_
#define _ENDPOINT_IPV4_H_

#include "endpoint.h"

#include <netinet/in.h>

class endpoint_ipv4 : public endpoint
{
public:
    endpoint_ipv4();

    endpoint_ipv4( const std::string& ip_address, std::uint16_t port );

    ~endpoint_ipv4() = default;

    std::string get_ip_address() noexcept final;

    std::uint16_t get_port() noexcept final;

    int get_domain() noexcept final;

    int get_type() noexcept final;

    int get_protocol() noexcept final;

    struct sockaddr* get_sockaddr() noexcept final;

    socklen_t get_sockaddr_size() noexcept final;

    int get_backlong() noexcept final;

    endpoint_ipv4( const endpoint_ipv4& copy );

    endpoint_ipv4& operator=( const endpoint_ipv4& copy ) = default;

    endpoint_ipv4( endpoint_ipv4&& other ) = default;

    endpoint_ipv4& operator=( endpoint_ipv4&& other ) = default;

private:
    struct sockaddr_in sock_address4_;     ///!< структара ip версии 4
};

#endif //_ENDPOINT_IPV4_H_