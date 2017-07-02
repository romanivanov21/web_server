/**
 *  Файл: slave_connection.h
 *
 *  Описание: общий интерфейс взалимодействия с клиентом, через сокет клиента
 *
 *  Автор: Иванов Роман Витальевич (с)
 */

#ifndef _SLAVE_CONNECTION_H_
#define _SLAVE_CONNECTION_H_

//internal
#include "event.h"
#include "byte_vector.h"

//std
#include <vector>

namespace network
{
    class slave_connection
    {
    public:
        slave_connection() = default;

        virtual ~slave_connection() = default;

        virtual std::int64_t send_data
          (const std::vector<byte>&) noexcept = 0;

        virtual std::vector<byte>
          receive_data_all() const noexcept = 0;

        virtual std::int64_t receive_data(std::vector<byte>&) = 0;

        virtual int get_socket() const noexcept = 0;

        slave_connection(const slave_connection&) = delete;

        slave_connection& operator=(const slave_connection&) = delete;

        slave_connection(slave_connection&&) = default;

        slave_connection& operator=(slave_connection&&) = default;

    public:
        /**
         * @brief соединение разорвано
         */
        event<void> disconnected;
    };
}

#endif //_CLIENT_CONNECTION_H_