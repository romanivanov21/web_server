/**
 *  Файл: tcp_connection_creator.h
 *
 *  Описание: создатель экземпляра класса tcp_connection
 */

#ifndef _TCP_CONNECTION_CREATOR_H_
#define _TCP_CONNECTION_CREATOR_H_

#include "connection_creator.h"

class tcp_connection_creator : public connection_creator
{
public:
    tcp_connection_creator() = default;
    ~tcp_connection_creator() = default;

    /**
     * @brief получение экземпляра класса tcp_connection
     *
     * @return connection* указатель на созданный объект
     */
    connection* get_connection() noexcept override;

    tcp_connection_creator(const tcp_connection_creator& copy) = delete;
    tcp_connection_creator& operator=(const tcp_connection_creator& copy) = delete;
};

#endif //_TCP_CONNECTION_CREATOR_H_