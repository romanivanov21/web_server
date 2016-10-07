/**
 *  Файл: connection.h
 *
 *  Описание: абстрактный класс, описывающий сетевое соединение
 */

#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <unistd.h>
#include <netinet/in.h>

class connection
{
public:
    connection() = default;
    virtual ~connection() = default;

    /**
     * @brief создание слушающего сокета
     */
    virtual void create_socket(const char* addr, uint16_t port) = 0;

    /**
     * @brief ожидание подключения
     */
    virtual void wait_accept() = 0;

    /**
     * @brief прием данных
     *
     * @retun количество принятых байт
     */
    virtual size_t recv_data(char* buffer, const int& len) = 0;

    /**
     * @brief передача данных
     *
     * @retun количество переданных байт
     */
    virtual size_t send_data(char* buffer, const int& len) = 0;

    /**
     * @brief получение номера сокета
     *
     * @retun номер сокета
     */
    virtual int get_socket() = 0;

    /**
     * @brief закрытие слушающего сокета
     */
    virtual void close_socket() = 0;

    connection(const connection& copy ) = delete;
    connection& operator=(const connection& copy) = delete;
};

#endif //_CONNECTION_H_