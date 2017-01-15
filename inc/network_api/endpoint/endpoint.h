/**
 *  Файл: endpoint.h
 *
 *  Описание: интерфейс параметров сетевого соединения
 *
 */

#ifndef _ENDPOINT_H_
#define _ENDPOINT_H_

#include <string>
#include <netinet/in.h>

class endpoint
{
public:
    endpoint() = default;

    virtual ~endpoint() = default;

    /**
     * @brief получение ip адреса
     */
    virtual std::string get_ip_address() const noexcept = 0;

    /**
     * @brief получение пота сетевого соединения
     */
    virtual std::uint16_t get_port() const noexcept = 0;

    /**
     * @brief получение домена сокета
     */
    virtual int get_domain() const noexcept  = 0;

    /**
     * @brief получение типа сокета
     */
    virtual int get_type() const noexcept = 0;

    /**
     * @brief получение транспортного соекта
     */
    virtual int get_protocol() const noexcept = 0;

    /**
     * @brief получение структуры sockaddr
     */
    virtual struct sockaddr* get_sockaddr() const noexcept = 0;

    /**
     * @brief получение размера структуры sockaddr
     */
    virtual socklen_t get_sockaddr_size() const noexcept = 0;

    /**
     * @brief максимального значения очереди listen
     */
    virtual int get_backlong() const noexcept = 0;

    endpoint( const endpoint& copy ) = default;

    endpoint& operator=( const endpoint& copy ) = default;

    endpoint( endpoint&& other ) = default;

    endpoint& operator=( endpoint&& other ) = default;
};

#endif //_ENDPOINT_H_