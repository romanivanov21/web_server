/**
 *  Файл: tcp_connection_creator.h
 *
 *  Описание:
 */

#ifndef _TCP_CONNECTION_CREATOR_H_
#define _TCP_CONNECTION_CREATOR_H_

#include "connection.h"
#include "connection_creator.h"

class tcp_connection_creator : public connection_creator
{
 public:
    tcp_connection_creator( );
    ~tcp_connection_creator( );

    connection* get_connection( ) override;
};

#endif //_TCP_CONNECTION_CREATOR_H_