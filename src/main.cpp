/**
 *  Файл: main.cpp
 *
 *  Описание: реализация функции main - точка входа в приложение
 */

#include "types.h"
#include "access_log.h"
#include "error_log.h"
#include "master_loader.h"
#include "server_loader.h"
#include "connection_creator.h"
#include "tcp_connection_creator.h"
#include "worker_process.h"
#include "worker_pocess_creator.h"
#include "current_system_info.h"

#include <vector>
#include <algorithm>
#include <memory>

//First Commit Branch Daemon
int main( int argc, char **argv )
{
	//иницаилизация системы конфигурации сервера
	server_config &config = server_config::get_instance();

	//инициализации системы логов сервера
	access_log& server_access_log = access_log::get_instance();
	server_access_log.create_log_file( config.get_config()->ACCESS_LOG_ );

	error_log& server_error_log = error_log::get_instance();
	server_error_log.create_log_file( config.get_config()->ERROR_LOG_ );

	//инициализации системы создания сетевого соединения
	std::shared_ptr<connection_creator> connection_creator( new tcp_connection_creator( ) );
	std::shared_ptr<connection> tcp_connect ( connection_creator->get_connection() );

	//создание процессов
	std::shared_ptr<worker_process_creator> process_creator( new worker_process_creator( ) );
	auto *worker_processes = new std::vector<process* >();
	for( auto i = 0; i < current_system_info::get_instance().get_proc_kernel_count(); i++ )
	{
		worker_processes->push_back( process_creator->get_process() );
	}

	//Запуск процессов
	std::for_each( worker_processes->begin(), worker_processes->end(), [] ( process *item )
	{
		if( item->start_process() )
		{
			access_log::get_instance().write_log("New worker process was started.");
		}
		else
		{
			error_log::get_instance().write_log("Failed to create new worker process");
		}
	});

	//удаление процессов
	std::for_each( worker_processes->begin(), worker_processes->end(), []( auto item ) { delete item; } );
	delete worker_processes;

	return 0;
}

