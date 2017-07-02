#ifndef _ENDPOINT_IPV6_H_
#define _ENDPOINT_IPV6_H_

//internal
#include "endpoint.h"

//linux
#include <netinet/in.h>

namespace network
{
    class endpoint_ipv6 : public network::endpoint
    {
    public:
        endpoint_ipv6(const std::string& ip_address, std::uint16_t port);

        ~endpoint_ipv6() = default;

        std::string get_ip_address() noexcept final;

        std::uint16_t get_port() noexcept final;

        int get_domain() noexcept final;

        int get_type() noexcept final;

        int get_protocol() noexcept final;

        struct sockaddr * get_sockaddr() noexcept final;

        socklen_t get_sockaddr_size() noexcept final;

        int get_backlong() noexcept final;

        endpoint_ipv6(const endpoint_ipv6& copy) = default;

        endpoint_ipv6& operator=(const endpoint_ipv6& copy) = default;

        endpoint_ipv6(endpoint_ipv6&& other) = default;

        endpoint_ipv6& operator=(endpoint_ipv6& other) = default;
    private:
        std::string ip_address_;               ///!<

        std::uint16_t port_;                   ///!<

        struct sockaddr_in6 sock_address6_;    ///!<
    };

} //namespace

#endif //_ENDPOINT_IPV6_H_