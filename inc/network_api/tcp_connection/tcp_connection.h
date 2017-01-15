/**
 *  Файл: tcp_connection.h
 *
 *  Описание: реализация сетевого соединения с клиентом по протоколу tcp
 *
 *  Автор: Иванов Роман Витальевич (с)
 */

#ifndef _TCP_CONNECTION_H_
#define _TCP_CONNECTION_H_

#include "connection_creator.h"
#include "connection.h"

#include <cstddef>

class tcp_connection : public connection
{
public:
    explicit tcp_connection( int slave_socket );

    ~tcp_connection();

    std::int64_t send_data( const std::vector<byte>& buffer ) const noexcept final;

    std::int64_t send_data( const std::string& buffer ) const noexcept final;

    std::int64_t receive_data( std::vector<byte>& buffer ) const noexcept final;

    std::int64_t receive_data( std::string& buffer ) const noexcept final;

    int get_slave_socket() const noexcept final;

    tcp_connection( const tcp_connection& copy ) = delete;

    tcp_connection& operator=( const tcp_connection& copy ) = delete;

    tcp_connection( tcp_connection&& other ) = default;

    tcp_connection& operator=( tcp_connection&& other ) = default;

private:
    int slave_socket_;     //!< дескриптор клиентского сокета
};

#endif // _TCP_CONNECTION_H_