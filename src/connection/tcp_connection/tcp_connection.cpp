#include "tcp_connection.h"

#include <arpa/inet.h>

void tcp_connection::create_socket(const char* addr, uint16_t port)
{
    master_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = inet_addr(addr);
    bind(master_socket, (struct sockaddr* )(&sock_addr), sizeof(sock_addr));

    listen(master_socket, SOMAXCONN);
}

void tcp_connection::wait_accept()
{
    slave_socket = accept(master_socket, NULL, NULL);
}

size_t tcp_connection::recv_data(char* buffer, const int& len)
{
    return recv(slave_socket, buffer, len, MSG_NOSIGNAL);
}

size_t tcp_connection::send_data(char* buffer, const int& len)
{
    return send(slave_socket, buffer, len, MSG_NOSIGNAL);
}

int tcp_connection::get_socket()
{
    return slave_socket;
}

void tcp_connection::close_socket()
{
    shutdown(slave_socket, SHUT_RDWR);
    close(slave_socket);
}

