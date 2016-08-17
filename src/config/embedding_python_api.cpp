#include "embedding_pyhton_api.h"

#include <cassert>
#include <stdexcept>

embedding_python_api::embedding_python_api() : pName( nullptr ), pModule( nullptr ), pFunc( nullptr )
{
    Py_Initialize();

    //установка и нстройка путей до python модулей по умолчаиню
    PyRun_SimpleString( "import sys" );
    PyRun_SimpleString( "sys.path.append('/usr/lib/python2.7/') ");
    PyRun_SimpleString( "sys.path.append('/usr/lib/python2.7/dist-packages')" );
    PyRun_SimpleString( "sys.path.append('/usr/lib/python2.7/lib-dynload') " );
}

embedding_python_api::~embedding_python_api() noexcept
{
    if( pModule )
        Py_DECREF( pModule );
    if( pName )
        Py_DECREF( pName );

    Py_Finalize();
}

void embedding_python_api::py_import_module( const std::string &module_name )
{
    assert( !module_name.empty() );

    pName = PyString_FromString( module_name.c_str() );
    pModule = PyImport_Import( pName );
    if( pModule == nullptr )
    {
#ifdef _DEBUG
        PyErr_Print();
#endif //_DEBUG
        throw std::runtime_error( "Can not import module" );
    }
}

void embedding_python_api::py_set_module_path( const std::string& module_patch ) noexcept
{
    assert( !module_patch.empty() );

    //Установка и настройка путей до используемых python модулей
    PyRun_SimpleString( "import sys");
    const std::string cmd = "sys.path.append('" + module_patch + "')";
    PyRun_SimpleString( cmd.c_str() );
}

void embedding_python_api::py_function_call( const std::string &function_name, char *format, ... )
{
    assert( !function_name.empty() );
    assert( pModule != nullptr );

    if( pModule != nullptr )
    {
        pFunc = PyObject_GetAttrString( pModule, function_name.c_str() );
        if( ( pFunc != nullptr ) && ( PyCallable_Check( pFunc ) ) )
        {
            PyObject_CallFunction( pFunc, format );
        }
        else
        {
#ifdef _DEBUG
            PyErr_Print();
#endif //_DEBUG
        }
    }
    else
    {
#ifdef _DEBUG
        PyErr_Print();
#endif //_DEBUG
    }
}