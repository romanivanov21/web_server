/**
 *  Файл: main.cpp
 *
 *  Описание: реализация функции main - точка входа в приложение
 */

#include "types.h"
#include "access_log.h"
#include "error_log.h"
#include "server_config.h"
#include "server_config_exception.h"
#include "worker_process.h"
#include "worker_process_creator.h"
#include "master_process_creator.h"

#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>

int main( int argc, char **argv )
{
	//иницаилизация системы конфигурации сервера
	server_config &config = server_config::get_instance();
	try
	{
		config.load_config_file("/..");
	}
	catch( server_config_exception &ex )
	{
		std::cout<<ex.what()<<std::endl;
	}
	catch(...)
	{
		std::cout<<"Config file error"<<std::endl;
	}

	//инициализации системы логов сервера
	access_log& server_access_log = access_log::get_instance();
	server_access_log.create_log_file( config.get_config()->ACCESS_LOG_ );

	error_log& server_error_log = error_log::get_instance();
	server_error_log.create_log_file( config.get_config()->ERROR_LOG_ );

	//создание мастер процесса
	std::shared_ptr<process_creator> m_process_creator( new master_process_creator() );
	pid_t pid = m_process_creator->create_process();
	if( !pid )
	{
		process* master_process = m_process_creator->get_process();
		master_process->start_process();
	}
	else if( pid == -1 )
	{
		std::cout<<"Can not create master process"<<std::endl;
	}

	return 0;
}

