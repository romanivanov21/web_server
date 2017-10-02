#include "http_session.h"
#include "slave_connection.h"

using namespace network;

void http_session::init
    (const slave_connection_unique_ptr& connection) noexcept
{
	
}

void http_session::on_error() noexcept
{

}

void http_session::on_timeout() noexcept
{

}

void http_session::done() noexcept
{

}

void http_session::on_receive_data
  (const byte_vector& buffer) noexcept
{

}

void http_session::on_idle() noexcept
{

}