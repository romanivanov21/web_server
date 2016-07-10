/**
 *  Файл: main.cpp
 *
 *  Описание:
 */

#include "types.h"
#include "master_loader.h"
#include "server_loader.h"
#include "connection.h"
#include "connection_creator.h"
#include "tcp_connection_creator.h"

#include <memory>

int main( int argc, char **argv )
{
	int status = default_error_code;
	int pid = default_error_code;

	std::shared_ptr<master_loader> loader( new  server_loader( ) );
	std::shared_ptr<connection_creator> creator( new tcp_connection_creator( ) );
	std::shared_ptr<connection> connect ( creator->get_connection() );

	return 0;
}

