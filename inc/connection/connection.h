/**
 *  Файл: connection.h
 *
 *  Описание: абстрактный класс, описывающий сетевое соединение
 */

#ifndef _CONNECTION_H_
#define _CONNECTION_H_

class connection
{
 public:
    connection() = default;
    virtual ~connection() = default;

    connection( const connection &copy ) = delete;
    connection& operator=( const connection &copy ) = delete;
};

#endif //_CONNECTION_H_