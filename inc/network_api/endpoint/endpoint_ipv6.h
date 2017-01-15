/**
 *  Файл: endpoint_ipv6.h
 *
 *  Описание: параметры сетевого соединения ip версии 6
 */

#ifndef _ENDPOINT_IPV6_H_
#define _ENDPOINT_IPV6_H_

#include "endpoint.h"

#include <netinet/in.h>

class endpoint_ipv6 : public endpoint
{
public:
    endpoint_ipv6();

    /**
     * @brief конструктор с парметром
     *
     * @param port порт
     */
    explicit endpoint_ipv6( std::uint16_t port );

    /**
     * @brief конструктор с параметрами
     *
     * @param ip_address ip адрес
     * @param port порт
     */
    endpoint_ipv6( const std::string& ip_address, std::uint16_t port );

    ~endpoint_ipv6() = default;

    /**
     * @brief получение ip адреса
     */
    std::string get_ip_address() const noexcept final;

    /**
     * @brief получение пота сетевого соединения
     */
    std::uint16_t get_port() const noexcept final;

    /**
     * @brief получение домена сокета
     */
    int get_domain() const noexcept final;

    /**
     * @brief получение типа сокета
     */
    int get_type() const noexcept final;

    /**
     * @brief получение транспортного соекта
     */
    int get_protocol() const noexcept final;

    /**
     * @brief получение структуры sockaddr
     */
    struct sockaddr* get_sockaddr() const noexcept final;

    /**
    * @brief получение размера структуры sockaddr
    */
    socklen_t get_sockaddr_size() const noexcept final;

    /**
     * @brief максимального значения очереди listen
     */
    int get_backlong() const noexcept final;

    endpoint_ipv6( const endpoint_ipv6& copy ) = default;

    endpoint_ipv6& operator=( const endpoint_ipv6& copy ) = default;

    endpoint_ipv6( endpoint_ipv6&& other ) = default;

    endpoint_ipv6& operator=( endpoint_ipv6& other ) = default;
private:
    std::string ip_address_;               ///!<

    std::uint16_t port_;                   ///!<

    struct sockaddr_in6 sock_address6_;    ///!<
};

#endif //_ENDPOINT_IPV6_H_