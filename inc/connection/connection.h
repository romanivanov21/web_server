/**
 *  Файл: connection.h
 *
 *  Описание:
 */

#ifndef _CONNECTION_H_
#define _CONNECTION_H_

class connection
{
 public:
    connection( ) { }
    virtual ~connection( ) { }

    connection( const connection &copy ) = delete;
    connection& operator=( const connection &copy ) = delete;
};

#endif //_CONNECTION_H_