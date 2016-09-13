#include "tcp_connection.h"
#include "tcp_connection_creator.h"

connection* tcp_connection_creator::get_connection() noexcept
{
    return new tcp_connection();
}