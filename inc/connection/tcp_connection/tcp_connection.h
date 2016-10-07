/**
 *  Файл: tcp_connection.h
 *
 *  Описание: класс для работы с сетевым соединением, передающий
 *            данные на транспортном уровене по протоколу tcp
 */

#ifndef _TCP_CONNECTION_H_
#define _TCP_CONNECTION_H_

#include <unistd.h>

#include "connection.h"

class tcp_connection : public connection
{
public:
    tcp_connection() = default;
    ~tcp_connection() = default;

    /**
     * @brief создание слушающего tcp сокета
     */
    virtual void create_socket(const char* addr, uint16_t port) override;

    /**
     * @brief ожидание tcp подключения
     */
    virtual void wait_accept() override;

    /**
     * @brief прием данных
     *
     * @retun количество принятых байт
     */
    virtual size_t recv_data(char* buffer, const int& len) override;

    /**
     * @brief передача данных
     *
     * @retun количество переданных байт
     */
    virtual size_t send_data(char* buffer, const int& len) override;

    /**
     * @brief получение номера сокета
     *
     * @retun номер сокета
     */
    virtual int get_socket() override;

    /**
     * @brief закрытие слушающего tcp сокета
     */
    virtual void close_socket() override;

    tcp_connection(const tcp_connection& copy) = delete;
    tcp_connection & operator=(const tcp_connection& copy) = delete;

private:
    int master_socket;
    int slave_socket;
};

#endif //_TCP_CONNECTION_H_