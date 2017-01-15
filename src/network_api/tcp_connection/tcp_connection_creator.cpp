#include "tcp_connection/tcp_connection_creator.h"
#include "connection_except.h"

#include <unistd.h>
#include <cassert>
#include <fcntl.h>
#include <cstring>
#include <logs/access_log.h>

tcp_connection_creator::tcp_connection_creator() : master_socket_( default_error_code ) { }

tcp_connection_creator::tcp_connection_creator( std::unique_ptr<endpoint> ep )
  : tcp_connection_creator()
{
    assert( ep.get() );
    ep_ =  std::move( ep );

    assert( ep_.get() );
    assert( !( ep_->get_ip_address().empty() ) );
    assert( ( ep_->get_port() > 0 ) && ( ep_->get_port() < 65000 ) );

    master_socket_ = socket( ep_->get_domain(), ep_->get_type(), ep_->get_protocol() );
    if( master_socket_ == default_error_code )
        throw connection_except( connection_except::error_type::SOCKET_ERROR );

    sock_bind();
    sock_listen();
}

tcp_connection_creator::~tcp_connection_creator()
{
    if( master_socket_ > 0 )
    {
        close( master_socket_ );
    }
}

std::unique_ptr<connection> tcp_connection_creator::get_connection()
{
    int slave_socket = accept( master_socket_, nullptr, nullptr );
    if( slave_socket == default_error_code )
    {
        access_log::get_instance()->save_log( "Master process start 67" );
        throw connection_except( connection_except::error_type::ACCEPT_ERROR );
    }
    return std::make_unique<tcp_connection>( slave_socket );
}

std::unique_ptr<connection> tcp_connection_creator::get_connection( std::unique_ptr<endpoint>& c_ep )
{
    assert( c_ep.get() );

    int slave_socket = default_error_code;
    if( ( c_ep.get() ) || ( c_ep->get_domain() == ep_->get_domain() ) )
    {
        socklen_t size = c_ep->get_sockaddr_size();
        slave_socket = accept( master_socket_, c_ep->get_sockaddr(), &size );
        if( slave_socket == default_error_code )
        {
            throw connection_except( connection_except::error_type::ACCEPT_ERROR );
        }
    }
    else
    {
        throw std::logic_error( "Param of method error" );
    }
    return std::make_unique<tcp_connection>( slave_socket );
}

int tcp_connection_creator::get_master_socket() noexcept
{
    return master_socket_;
}

void tcp_connection_creator::set_reusaddr() const
{
    const int option_value = 1;
    if( setsockopt( master_socket_, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof( option_value ) ) == default_error_code )
    {
        throw connection_except( connection_except::error_type::SET_REUSADDR_ERROR );
    }
}

void tcp_connection_creator::set_nonblock() const
{
    int res = default_error_code;
    int flags = 0;
#if defined( O_NONBLOCK )
    if( ( flags = fcntl( master_socket_, F_GETFL, 0 ) ) == default_error_code )
        flags = 0;
    res = fcntl( master_socket_, F_SETFL, flags | O_NONBLOCK );
#else
    ﻿flags = 1;
    res =  ioctl(server_io_socket_, FIOBIO, &flags);
#endif
    if( res == default_error_code )
    {
        throw connection_except( connection_except::error_type::SET_NONBLOCK_ERROR );
    }
}

void tcp_connection_creator::set_timeout( const connection_creator::timeout& time ) const
{
    struct timeval tv = { 0 };
    if( ( time.send_time_s_ ) || ( time.send_time_us_ ) )
    {
        tv.tv_sec = time.send_time_s_;
        tv.tv_usec = time.send_time_us_;
        if( setsockopt( master_socket_, SOL_SOCKET, SO_SNDTIMEO, ( char *)&tv, sizeof( tv ) ) == default_error_code )
        {
            throw connection_except( connection_except::error_type::SET_TIMEOUT_ERROR );
        }
    }
    if( ( time.rcv_time_s_ ) || ( time.rcv_time_us_ ) )
    {
        tv.tv_sec = time.rcv_time_s_;
        tv.tv_usec = time.rcv_time_us_;
        if( setsockopt( master_socket_, SOL_SOCKET, SO_RCVTIMEO, ( char *)&tv, sizeof( tv ) ) == default_error_code )
        {
            throw connection_except( connection_except::error_type::SET_TIMEOUT_ERROR );
        }
    }
}

void tcp_connection_creator::sock_bind() const
{
    if( ( bind( master_socket_, ep_->get_sockaddr(), ep_->get_sockaddr_size() ) ) == default_error_code )
    {
        throw connection_except::error_type::BIND_ERROR;
    }
}

void tcp_connection_creator::sock_listen() const
{
    if( listen( master_socket_, ep_->get_backlong() ) == default_error_code )
    {
        throw connection_except::error_type::LISTEN_ERROR;
    }
}