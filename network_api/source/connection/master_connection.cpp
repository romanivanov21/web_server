#include "master_connection.h"

using network::master_connection;

void master_connection::connected_callback
  (connected_function const& f) noexcept
{
    connected.connect(f);
}

void master_connection::disconnected_callback
  (disconnected_function const& f) noexcept
{
    disconnected.connect(f);
}

void master_connection::timeout_callback
  (timeout_function const& f) noexcept
{
    timeout.connect(f);
}

void master_connection::error_callback
  (connection_error_function const &f) noexcept
{
    error.connect(f);
}