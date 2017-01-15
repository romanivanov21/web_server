#ifndef _ENDPOINT_IPV6_H_
#define _ENDPOINT_IPV6_H_

#include "endpoint.h"

#include <netinet/in.h>

class endpoint_ipv6 : public endpoint
{
public:
    endpoint_ipv6();

    endpoint_ipv6( const std::string& ip_address, std::uint16_t port );

    ~endpoint_ipv6() = default;

    std::string get_ip_address() noexcept final;

    std::uint16_t get_port() noexcept final;

    int get_domain() noexcept final;

    int get_type() noexcept final;

    int get_protocol() noexcept final;

    struct sockaddr* get_sockaddr() noexcept final;

    socklen_t get_sockaddr_size() noexcept final;

    int get_backlong() noexcept final;

    endpoint_ipv6( const endpoint_ipv6& copy ) = default;

    endpoint_ipv6& operator=( const endpoint_ipv6& copy ) = default;

    endpoint_ipv6( endpoint_ipv6&& other ) = default;

    endpoint_ipv6& operator=( endpoint_ipv6& other ) = default;
private:
    std::string ip_address_;               ///!<

    std::uint16_t port_;                   ///!<

    struct sockaddr_in6 sock_address6_;    ///!<
};

#endif //_ENDPOINT_IPV6_H_