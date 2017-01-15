/**
 *  Файл: connection.h
 *
 *  Описание: общий интерфейс сетевого соединения с клиентом, через сокет
 *            основан на идеоме RAII
 */

#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include "types.h"

#include <netinet/in.h>
#include <string.h>
#include <string>
#include <vector>

class connection
{
public:
    connection() = default;

    virtual ~connection() = default;

    /**
     * @brief получение дескриптора клиентского соекта
     *
     * @return дескриптор
     */
    virtual int get_slave_socket() const noexcept = 0;

    /**
     * @brief отправка данных
     *
     * @param buffer вектор с данными
     */
    virtual std::int64_t send_data( const std::vector<byte>& buffer ) const noexcept = 0;

    /**
     * @brief отправка данных
     *
     * @param buffer строка с данными
     *
     * @return число отправленных байт
     */
    virtual std::int64_t send_data( const std::string& buffer ) const noexcept = 0;

    /**
     * @brief чтения данных из сетевого соединения
     *
     * @param buffer буффера для чтения данных
     *
     * @return число полученных байт данных
     */
    virtual std::int64_t receive_data( std::vector<byte>& buffer ) const  noexcept = 0;

    /**
     * @brief чтение строки данных из сетевого соединения
     *
     * @param buffer строка для чтения данных
     *
     * @return число полученных байт данных
     */
    virtual std::int64_t receive_data( std::string& buffer ) const noexcept = 0;

    connection( const connection& copy ) = delete;

    connection& operator=( const connection& copy ) = delete;

    connection( connection&& other ) = delete;

    connection& operator=( connection&& other ) = delete;
};

#endif //_CONNECTION_H_