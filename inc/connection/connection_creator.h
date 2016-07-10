/**
 *  Файл: connection_creator.h
 *
 *  Описание:
 */

#ifndef _CONNECTION_CREATOR_H_
#define _CONNECTION_CREATOR_H_

#include "connection.h"

class connection_creator
{
 public:
    connection_creator( ) { }
    ~connection_creator( ) { }

    virtual connection* get_connection( ) = 0;

    connection_creator( const connection_creator &copy ) = delete;
    connection_creator& operator=( const connection_creator &copy ) = delete;
};
#endif //_CONNECTION_CREATOR_H_