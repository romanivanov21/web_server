#ifndef _ENDPOINT_IPV4_H_
#define _ENDPOINT_IPV4_H_

//internal
#include "endpoint.h"

namespace network
{
    class endpoint_ipv4 : public network::endpoint
    {
    public:
        endpoint_ipv4(network::connection_port port);

        endpoint_ipv4(const std::string& ip_address,
                      network::connection_port port);

        ~endpoint_ipv4() override;

        std::string get_ip_address() noexcept final;

        std::uint16_t get_port() noexcept final;

        int get_domain() const noexcept final;

        int get_type() noexcept final;

        int get_protocol() noexcept final;

        struct sockaddr* get_sockaddr() noexcept final;

        socklen_t get_sockaddr_size() noexcept final;

        int get_backlong() noexcept final;

        endpoint_ipv4(const endpoint_ipv4& other);

        endpoint_ipv4& operator=(const endpoint_ipv4& other);

        endpoint_ipv4(endpoint_ipv4&& other);

        endpoint_ipv4& operator=(endpoint_ipv4&& other);
    private:
        struct impl;
        std::unique_ptr<impl> d_;
    };
}

#endif //_ENDPOINT_IPV4_H_
