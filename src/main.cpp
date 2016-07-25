/**
 *  Файл: main.cpp
 *
 *  Описание: реализация функции main - точка входа в приложение
 */
#include "daemon.h"

#include <stdexcept>
#include <iostream>

int main( int argc, char **argv )
{
	try
	{
		daemon::init_config( );
		daemon::init_access_log( );
		daemon::init_error_log( );
	}
	catch(...)
	{

	}
	//сделай сингтон
	auto *dem = new daemon( );

	try
	{
		dem->start_daemon( );
	}
	catch( std::runtime_error &ex )
	{
		std::cout<<ex.what()<<std::endl;
	}
	delete dem;

	return 0;
}
