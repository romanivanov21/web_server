#include "tcp_connection.h"

#include <arpa/inet.h>

void tcp_connection::create_connection(const char* addr, uint16_t port)
{
    if (descriptor.master_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) == -1)
    {
        throw;
    }
    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = inet_addr(addr);
    if (bind(descriptor.master_socket, (struct sockaddr* )(&sock_addr), sizeof(sock_addr)) == -1)
    {
        throw;
    }

    listen(descriptor.master_socket, SOMAXCONN);
}

void tcp_connection::wait_to_connect()
{
    if (descriptor.slave_socket = accept(descriptor.master_socket, NULL, NULL) == -1)
    {
        throw;
    }
}

size_t tcp_connection::recv_data(std::vector<char> buffer, const int& len)
{
    size_t res;
    if (res = recv(descriptor.slave_socket, reinterpret_cast<char*>(buffer.data()), len, MSG_NOSIGNAL) == -1)
    {
        throw;
    }
    return res;
}

size_t tcp_connection::send_data(std::vector<char> buffer, const int& len)
{
    size_t res;
    if (res = send(descriptor.slave_socket, reinterpret_cast<char*>(buffer.data()), len, MSG_NOSIGNAL) == -1)
    {
        throw;
    }
    return res;
}

int tcp_connection::get_socket()
{
    if (!descriptor.slave_socket)
    {
        return descriptor.slave_socket;
    }
    else
    {
        throw;
    }
}

void tcp_connection::close_socket()
{
    if (shutdown(descriptor.slave_socket, SHUT_RDWR) == -1)
    {
        throw;
    }
    if (close(descriptor.slave_socket) == -1)
    {
        throw;
    }
}

