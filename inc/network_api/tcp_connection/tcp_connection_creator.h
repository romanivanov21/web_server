#ifndef _TCP_CONNECTION_CREATOR_H_
#define _TCP_CONNECTION_CREATOR_H_

#include "tcp_connection.h"
#include "connection_creator.h"
#include "endpoint.h"

#include <netinet/in.h>

class tcp_connection_creator : public connection_creator
{
public:
    tcp_connection_creator( std::unique_ptr<endpoint> ep );

    ~tcp_connection_creator();

    std::unique_ptr<connection> get_connection() final;

    std::unique_ptr<connection> get_connection( std::unique_ptr<endpoint>& ep ) final;

    int get_master_socket() noexcept final;

    void set_timeout( const connection_creator::timeout& t ) const final;

    void set_nonblock() const final;

    void set_reusaddr() const final;

    tcp_connection_creator( const tcp_connection_creator& copy ) = delete;

    tcp_connection_creator& operator=( const tcp_connection_creator& copy ) = delete;

    tcp_connection_creator( tcp_connection_creator&& other ) = default;

    tcp_connection_creator& operator=( tcp_connection_creator&& other ) = default;

private:
    /**
     *  @brief делегирующий конструктор
     */
    tcp_connection_creator();

    void sock_bind() const;

    void sock_listen() const;

private:
    int master_socket_;              ///!< дескриптор серверного сокета

    std::unique_ptr<endpoint> ep_;   ///!< структра с параметрами сетвого соединения
};

#endif // _TCP_CONNECTION_CREATOR_H_