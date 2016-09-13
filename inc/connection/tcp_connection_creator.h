/**
 *  Файл: tcp_connection_creator.h
 *
 *  Описание: создатель экземпляра класса tcp_connection
 */

#ifndef _TCP_CONNECTION_CREATOR_H_
#define _TCP_CONNECTION_CREATOR_H_

#include "connection.h"
#include "connection_creator.h"

class tcp_connection_creator : public connection_creator
{
 public:
    tcp_connection_creator() = default;
    ~tcp_connection_creator() = default;

    /**
     * @brief получение экземпляра класса tcp_connection
     *
     * @return указатель на объект tcp_connection
     */
    connection* get_connection() noexcept override;
};

#endif //_TCP_CONNECTION_CREATOR_H_