/**
 *  Файл: connection_creator.h
 *
 *  Описание: абстрактный создатеть соединений
 */

#ifndef _CONNECTION_CREATOR_H_
#define _CONNECTION_CREATOR_H_

#include "connection.h"

class connection_creator
{
public:
    connection_creator() = default;
    virtual ~connection_creator() = default;

    /**
     *  @brief получение экземпляра класса connection
     *
     * @return новый экзкмпляр класса connection
     */
    virtual connection* get_connection() noexcept = 0;

    connection_creator(const connection_creator& copy) = delete;
    connection_creator& operator=(const connection_creator& copy) = delete;
};
#endif //_CONNECTION_CREATOR_H_