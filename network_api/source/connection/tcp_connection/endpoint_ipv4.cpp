//internal
#include "endpoint_ipv4.h"

//std
#include <cstring>
#include <cassert>

//linux
#include <arpa/inet.h>

using namespace network;

struct endpoint_ipv4::impl
{
    struct sockaddr_in sock_address4_;     ///!< структара ip версии 4
};

endpoint_ipv4::endpoint_ipv4(const std::string& ip_address,
                             connection_port port) : d_(new impl())
{
    if(!d_) return;

    //!TODO: 65000
    assert(!ip_address.empty());
    assert((port > 0) && (port <= 65000));

    std::memset(&d_->sock_address4_, 0x00, sizeof(d_->sock_address4_));
    d_->sock_address4_.sin_family = AF_INET;
    d_->sock_address4_.sin_addr.s_addr = inet_addr(ip_address.c_str());
    d_->sock_address4_.sin_port = htons(port);
}

endpoint_ipv4::endpoint_ipv4(connection_port port) : d_(new impl())
{
    //!TODO: 65000
    assert((port > 0) && (port <= 65000));

    std::memset(&d_->sock_address4_, 0x00, sizeof(d_->sock_address4_));
    d_->sock_address4_.sin_family = AF_INET;
    d_->sock_address4_.sin_addr.s_addr = inet_addr("0.0.0.0");
    d_->sock_address4_.sin_port = htons(port);
}

endpoint_ipv4::~endpoint_ipv4()
{
    delete d_;
}

std::string endpoint_ipv4::get_ip_address() noexcept
{
    std::string res = std::string();
    res.resize(INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &d_->sock_address4_.sin_addr, &res[0], INET_ADDRSTRLEN );
    return res;
}

std::uint16_t endpoint_ipv4::get_port() noexcept
{
    uint16_t res = 0;
    res = htons(d_->sock_address4_.sin_port );
    return res;
}

int endpoint_ipv4::get_domain() const noexcept
{ return AF_INET; }

int endpoint_ipv4::get_type() noexcept { return SOCK_STREAM; }

int endpoint_ipv4::get_protocol() noexcept { return IPPROTO_TCP; }

struct sockaddr* endpoint_ipv4::get_sockaddr() noexcept
{
    return ( struct sockaddr* )&d_->sock_address4_;
}

endpoint_ipv4::endpoint_ipv4(const endpoint_ipv4& other) : d_(new impl())
{
    if(!d_) return;

    std::memcpy(&d_->sock_address4_, &other.d_->sock_address4_,
                    sizeof(d_->sock_address4_));
}

endpoint_ipv4& endpoint_ipv4::operator=(const endpoint_ipv4& other)
{
    if(this != &other)
    {
        std::memcpy(&d_->sock_address4_, &other.d_->sock_address4_,
                    sizeof(d_->sock_address4_));
    }
    return *this;
}

endpoint_ipv4::endpoint_ipv4(endpoint_ipv4&& other)
{
    d_ = other.d_;
    other.d_ = nullptr;
}

endpoint_ipv4& endpoint_ipv4::operator=(endpoint_ipv4&& other)
{
    std::swap(d_, other.d_);
    return *this;
}

socklen_t endpoint_ipv4::get_sockaddr_size() noexcept
{
    return sizeof( struct sockaddr_in );
}

int endpoint_ipv4::get_backlong() noexcept
{
    return SOMAXCONN;
}