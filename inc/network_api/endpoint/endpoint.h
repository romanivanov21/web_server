#ifndef _ENDPOINT_H_
#define _ENDPOINT_H_

#include <string>

#include <netinet/in.h>

class endpoint
{
public:
    endpoint() = default;

    virtual ~endpoint() = default;

    virtual std::string get_ip_address() noexcept = 0;

    virtual std::uint16_t get_port() noexcept = 0;

    virtual int get_domain() noexcept  = 0;

    virtual int get_type() noexcept = 0;

    virtual int get_protocol() noexcept = 0;

    virtual struct sockaddr* get_sockaddr() noexcept = 0;

    virtual socklen_t get_sockaddr_size() noexcept = 0;

    virtual int get_backlong() noexcept = 0;

    endpoint( const endpoint& copy ) = default;

    endpoint& operator=( const endpoint& copy ) = default;

    endpoint( endpoint&& other ) = default;

    endpoint& operator=( endpoint&& other ) = default;
};

#endif //_ENDPOINT_H_