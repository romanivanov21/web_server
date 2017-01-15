/**
 *  Файл: connection_creator.h
 *
 *  Описание: интерфейс для создания сетевого подключения через сокеты на стороне сервера
 */

#ifndef _CONNECTION_CREATOR_H_
#define _CONNECTION_CREATOR_H_

#include "connection.h"

#include "endpoint.h"

#include <memory>

class connection_creator
{
public:
    struct timeout
    {
        timeout()
        {
            send_time_s_ = 0;
            send_time_us_ = 0;
            rcv_time_s_ = 0;
            rcv_time_us_ = 0;
        }

        timeout( const std::uint32_t& send_time_s, const std::uint32_t& send_time_us, const std::uint32_t& rcv_time_s,
                 const std::uint32_t& rcv_time_us )
          : send_time_s_( send_time_s ), send_time_us_( send_time_us ),
            rcv_time_s_( rcv_time_s ), rcv_time_us_( rcv_time_us ) { }

        std::uint32_t send_time_s_;   //!< Таймаут на отправку данных в секундах
        std::uint32_t send_time_us_;  //!< Таймаут на отправку данных в нано секундах
        std::uint32_t rcv_time_s_;    //!< Таймаут на приём данных в секунтах
        std::uint32_t rcv_time_us_;   //!< Таймаут на приём данных в наносекундах
    };
public:
    connection_creator() = default;

    virtual ~connection_creator() = default;

    /**
     * @brief получение соединения с клиентом, без надобности информации о клиенте
     *
     * @return объект типа connection для работы с клиентом ( клиентским сокетом )
     */
    virtual std::unique_ptr<connection> get_connection() = 0;

    /**
     * @brief получение соединения с клиентом
     *
     * @param ep структра с информацией о клиенте
     *
     * @return объект типа connection для работы с клиентом ( клиентским сокетом )
     */
    virtual std::unique_ptr<connection> get_connection( std::unique_ptr<endpoint>& ep ) = 0;

    /**
     * @brief получение дескриптора серверного сокета
     *
     * @return дескриптор серверного сокета
     */
    virtual int get_master_socket() noexcept = 0;

    /**
     * @brief установка таймаута
     *
     * @param t таймаут
     */
    virtual void set_timeout( const timeout& t ) const = 0;

    /**
     * @brief перевод в неблакаружщий режим
     */
    virtual void set_nonblock() const = 0;

    /**
     * @brief установка опции reusaddr
     */
    virtual void set_reusaddr() const = 0;

    connection_creator( const connection_creator& copy ) = delete;

    connection_creator& operator=( const connection_creator& copy ) = delete;

    connection_creator( connection_creator&& other ) = default;

    connection_creator& operator=( connection_creator&& other ) = default;
};

#endif //_CONNECTION_CREATOR_H_