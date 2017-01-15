/**
 * Файл: tcp_connection_creator.h
 *
 * Описание: класс для создания tcp соединения через сокеты на стороне сервера
 */

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

    /**
     * @brief получение соединения с клиентом, без надобности информации о клиенте
     *
     * @throw connection_except
     *
     * @return объект типа connection для работы с клиентом ( клиентским сокетом )
     */
    std::unique_ptr<connection> get_connection() final;

    /**
     * @brief получение соединения с клиентом
     *
     * @param ep структра с информацией о клиенте
     *
     * @throw connection_except
     *
     * @return объект типа connection для работы с клиентом ( клиентским сокетом )
     */
    std::unique_ptr<connection> get_connection( std::unique_ptr<endpoint>& ep ) final;

    /**
     * @brief получение дескриптора серверного сокета
     *
     * @return дескриптор серверного сокета
     */
    int get_master_socket() noexcept final;

    /**
     * @brief установка таймаута
     *
     * @param t таймаут
     *
     * @throw connection_except
     */
    void set_timeout( const connection_creator::timeout& t ) const final;

    /**
     * @brief перевод в неблакаружщий режим tcp соединение
     *
     * @throw connection_except
     */
    void set_nonblock() const final;

    /**
     * @brief установка опции reusaddr tcp соединения
     *
     * @throw connection_except
     */
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

    /**
     * @brief вызов bind() и провека ошибок
     *
     * @throw connection_except
     */
    void sock_bind() const;

    /**
     * @brief вызов listen() и проверка ошибок
     *
     * @throw connection_except
     */
    void sock_listen() const;

private:
    int master_socket_;              //!< дескриптор серверного сокета

    std::unique_ptr<endpoint> ep_;   //!< структра с параметрами сетвого соединения
};

#endif // _TCP_CONNECTION_CREATOR_H_