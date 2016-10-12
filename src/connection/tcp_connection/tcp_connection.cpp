#include "tcp_connection.h"

#include <strings.h>
#include <arpa/inet.h>

void tcp_connection::create_connection(std::string ip_addr, uint16_t port)
{
    descriptor.master_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (descriptor.master_socket == -1)
    {
        throw;
    }

    int opt_value = 1;
    if (setsockopt(descriptor.master_socket, SOL_SOCKET, SO_REUSEADDR, &opt_value, sizeof(opt_value)) == -1)
    {
        throw;
    }

    struct sockaddr_in sock_addr;
    bzero(&sock_addr, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());

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

size_t tcp_connection::recv_data(std::vector<char>& buffer)
{
    size_t recv_bytes = recv(descriptor.slave_socket, buffer.data(), buffer.size(), MSG_NOSIGNAL);
    if (recv_bytes == -1)
    {
        throw;
    }
    return recv_bytes;
}

size_t tcp_connection::send_data(std::vector<char>& buffer)
{
    size_t send_bytes = send(descriptor.slave_socket, buffer.data(), buffer.size(), MSG_NOSIGNAL);
    if (send_bytes == -1)
    {
        throw;
    }
    return send_bytes;
}

int tcp_connection::get_socket()
{
    return descriptor.slave_socket;
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

