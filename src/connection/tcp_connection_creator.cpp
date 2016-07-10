#include "tcp_connection.h"
#include "tcp_connection_creator.h"

tcp_connection_creator::tcp_connection_creator( )
{

}

tcp_connection_creator::~tcp_connection_creator( )
{

}

connection* tcp_connection_creator::get_connection( )
{
    return new tcp_connection();
}