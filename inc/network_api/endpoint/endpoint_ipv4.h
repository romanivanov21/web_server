/**
 *  Файл: endpoint_ipv4.h
 *
 *  Описание: парметры стетвого соединения ip версии 4
 */

#ifndef _ENDPOINT_IPV4_H_
#define _ENDPOINT_IPV4_H_

#include "endpoint.h"

#include <netinet/in.h>

class endpoint_ipv4 : public endpoint
{
public:
    endpoint_ipv4();

    /**
     * @brief конструктор с парметром ( ip адресс по умолчанию 0.0.0.0 )
     *
     * @param port порт
     */
    explicit endpoint_ipv4( std::uint16_t port );

    /**
     * @brief конструктор с параметрами
     *
     * @param ip_address ip адрес
     * @param port порт
     */
    endpoint_ipv4( const std::string& ip_address, std::uint16_t port );

    ~endpoint_ipv4() = default;

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

    endpoint_ipv4( const endpoint_ipv4& copy );

    endpoint_ipv4& operator=( const endpoint_ipv4& copy );

    endpoint_ipv4( endpoint_ipv4&& other );

    endpoint_ipv4& operator=( endpoint_ipv4&& other );

private:
    struct sockaddr_in sock_address4_;     //!< структара ip версии 4
};

#endif //_ENDPOINT_IPV4_H_