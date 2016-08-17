/**
 *  Файл: main.cpp
 *
 *  Описание: реализация функции main - точка входа в приложение
 */

#include "daemon.h"

#include <python2.7/Python.h>
#include <stdexcept>
#include <iostream>

int main( int argc, char **argv )
{
	/*PyObject *pname, *pmodule, *pfunc;
	Py_Initialize();

	PySys_SetPath((char *)"/home/roman/work/C++ /web_server/src");
	std::cout<<Py_GetPath()<<std::endl;

	pname = PyString_FromString( "config_parser" );
	pmodule = PyImport_Import( pname );

	if ( pmodule )
	{
		pfunc = PyObject_GetAttrString( pmodule, "hello" );
		PyObject_CallObject(pfunc, NULL);
	}
	else
	{
		PyErr_Print();
	}

	Py_Finalize();
    */

	try
	{
		daemon::init_config( );
		//daemon::init_access_log( );
		//daemon::init_error_log( );
	}
	catch(...)
	{

	}
	//сделай сингтон
	/*auto *dem = new daemon( );

	try
	{
		dem->start_daemon( );
	}
	catch( std::runtime_error &ex )
	{
		std::cout<<ex.what()<<std::endl;
	}
	delete dem;
	*/

	return 0;
}
