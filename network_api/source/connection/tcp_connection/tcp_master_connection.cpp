#ifdef __linux__

//internal
#include "master_connection.h"
#include "tcp_master_connection.h"
#include "connection_error.h"
#include "endpoint.h"
#include "endpoint_ipv4.h"
#include "tcp_slave_connection.h"

//std
#include <cassert>

//linux
#include <unistd.h>
#include <fcntl.h>

using namespace network;

class tcp_master_connection::impl
{
public:
    bool set_reusaddr_opt() const noexcept;

    bool bind_socket();

    bool listen_socket();

    bool close_connection();

    static bool set_nonblock_opt(int fd);

public:
    int master_socket_ = default_error_code;

    endpoint_unique_ptr ep_ = nullptr;

    bool is_nonblock_ = false;

    bool is_reusaddr = false;
};

tcp_master_connection::tcp_master_connection()
  : d_(std::make_unique<impl>()) { }

tcp_master_connection::tcp_master_connection
  (endpoint_unique_ptr& ep)
  : tcp_master_connection()
{
    assert(ep.get() != nullptr);
    if(d_ && ep.get()) d_->ep_ = std::move(ep);
}

tcp_master_connection::~tcp_master_connection()
{
    if(!d_->close_connection())
    {
        error.emit(connection_error
          (connection_error::error_type::SOCKET_CLOSE_ERROR));
    }
    disconnected.emit();
}

tcp_master_connection::tcp_master_connection
  (tcp_master_connection&& other)
{
    //!TODO: не реализовано
}

tcp_master_connection& tcp_master_connection::operator=
  (tcp_master_connection&& other)
{
    //!TODO: не реализовано
}

void tcp_master_connection::create_connection()
{
    if((d_->master_socket_
          = socket(d_->ep_->get_domain(),
                   SOCK_STREAM, d_->ep_->get_protocol()))
       == default_error_code)
    {
        error.emit(connection_error
                     (connection_error::error_type::SOCKET_ERROR));
        return;
    }

    if(d_->is_reusaddr)

    if(!d_->bind_socket())
    {
        error.emit(connection_error
                     (connection_error::error_type::BIND_ERROR));
        return;
    }

    if(!d_->listen_socket())
    {
        error.emit(connection_error
                     (connection_error::error_type::LISTEN_ERROR));
        return;
    }
}

void tcp_master_connection::connect() noexcept
{
    endpoint_unique_ptr ep
      = std::make_unique<endpoint_ipv4>("127.0.0.1", 8888);

    //!TODO: ep don't us
    int slave_socket = accept(d_->master_socket_, nullptr, nullptr);
    if(slave_socket != default_error_code)
    {
        slave_connection_shared_ptr connection =
          std::make_shared<tcp_slave_connection>(slave_socket, ep);
        connected.emit(connection);
    }
    else if((d_->is_nonblock_) && (errno != EAGAIN))
    {
        error.emit(connection_error
               (connection_error::error_type::ACCEPT_ERROR));
        return;
    }
}

void tcp_master_connection::set_reusaddr()
{
    if(!d_->set_reusaddr_opt())
        error.emit(connection_error
                     (connection_error::error_type::SET_REUSADDR_ERROR));
    else
        d_->is_reusaddr = true;
}

bool tcp_master_connection::is_connection_nonblock() const
{
    return d_->is_nonblock_;
}

void tcp_master_connection::set_nonblock()
{
    if(!d_->set_nonblock_opt(d_->master_socket_))
        error.emit(connection_error
                     (connection_error::error_type::SET_NONBLOCK_ERROR));
    else
        d_->is_nonblock_ = true;
}

void tcp_master_connection::set_timeout
  (const connection_timeout& time)
{
    struct timeval tv = { 0 };
    if((time.send_time_s_ ) || (time.send_time_us_))
    {
        tv.tv_sec = time.send_time_s_;
        tv.tv_usec = time.send_time_us_;
        if(setsockopt(d_->master_socket_, SOL_SOCKET, SO_SNDTIMEO,
                       (char *)&tv, sizeof(tv))
            == default_error_code)
        {
            error.emit
              (connection_error
                 (connection_error::error_type::SET_TIMEOUT_ERROR));
        }
    }
    if((time.rcv_time_s_) || (time.rcv_time_us_))
    {
        tv.tv_sec = time.rcv_time_s_;
        tv.tv_usec = time.rcv_time_us_;
        if( setsockopt(d_->master_socket_, SOL_SOCKET, SO_RCVTIMEO,
                       (char *)&tv, sizeof(tv))
            == default_error_code )
        {
            error.emit(connection_error
              (connection_error::error_type::SET_TIMEOUT_ERROR));
        }
    }
}

bool tcp_master_connection::impl::set_reusaddr_opt() const noexcept
{
    const int option_value = 1;
    return ((setsockopt(master_socket_, SOL_SOCKET, SO_REUSEADDR,
                      &option_value, sizeof(option_value))) != default_error_code);
}

bool tcp_master_connection::impl::bind_socket()
{
    return (bind(master_socket_, ep_->get_sockaddr(),
                ep_->get_sockaddr_size()) != default_error_code);
}

bool tcp_master_connection::impl::listen_socket()
{
    return (listen(master_socket_, ep_->get_backlong()) != default_error_code);
}

bool tcp_master_connection::impl::close_connection()
{
    return (close(master_socket_) != default_error_code);
}

bool tcp_master_connection::impl::set_nonblock_opt(int fd)
{
    if(fd <= 0) return false;

    int res = 0;
    int flags = 0;
#if defined(O_NONBLOCK)
    if((flags = fcntl(fd, F_GETFL, 0))
       == default_error_code )
        flags = 0;
    res = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
    ﻿flags = 1;
    res =  ioctl(fd, FIOBIO, &flags);
#endif
    return (res != default_error_code);
}

#endif //__linux__
