#ifndef _ENDPOINT_H_
#define _ENDPOINT_H_

//internal
#include "connection_traits.h"

//std
#include <string>
#include <memory>

//linux
#include <netinet/in.h>

namespace network
{
    class endpoint
    {
    public:
        endpoint() = default;

        virtual ~endpoint() = default;

        virtual std::string get_ip_address() noexcept = 0;

        virtual std::uint16_t get_port() noexcept = 0;

        virtual int get_domain() const noexcept = 0;

        virtual int get_type() noexcept = 0;

        virtual int get_protocol() noexcept = 0;

        virtual struct sockaddr* get_sockaddr() noexcept = 0;

        virtual socklen_t get_sockaddr_size() noexcept = 0;

        virtual int get_backlong() noexcept = 0;

        endpoint(const endpoint& other) = default;

        endpoint& operator=(const endpoint& other) = default;

        endpoint(endpoint&& other) = default;

        endpoint& operator=(endpoint&& other) = default;
    };

} //namespace

#endif //_ENDPOINT_H_