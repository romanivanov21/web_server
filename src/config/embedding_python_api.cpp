#include "embedding_pyhton_api.h"
#include "server_config_exception.h"

#include <cassert>

embedding_python_api::embedding_python_api() : pName( nullptr ), pModule( nullptr ), pInstance( nullptr )
{
    Py_Initialize();

#ifdef __linux__
    //установка и нстройка путей до python модулей по умолчаиню
    PyRun_SimpleString( "import sys" );
    PyRun_SimpleString( "sys.path.append('/usr/lib/python2.7/') ");
    PyRun_SimpleString( "sys.path.append('/usr/lib/python2.7/dist-packages')" );
    PyRun_SimpleString( "sys.path.append('/usr/lib/python2.7/lib-dynload') " );
#endif //__linux__
}

embedding_python_api::~embedding_python_api() noexcept
{
    if( pModule )
        Py_DECREF( pModule );
    if( pName )
        Py_DECREF( pName );
    if( pInstance )
        Py_DECREF( pInstance );

    Py_Finalize();
}

void embedding_python_api::py_import_module( const std::string &module_name )
{
    assert( !module_name.empty() );

    pName = PyString_FromString( module_name.c_str() );
    pModule = PyImport_Import( pName );
    if( !pModule )
    {
        PyErr_Print();
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
    assert( pModule );

    if( pModule )
    {
        PyObject* pFunc = PyObject_GetAttrString( pModule, function_name.c_str() );
        if( ( pFunc ) && ( PyCallable_Check( pFunc ) ) )
        {
            PyObject_CallFunction( pFunc, format );
        }
        else
        {
#ifdef _DEBUG
            PyErr_Print();
#endif //_DEBUG
            throw std::runtime_error("");
        }
    }
    else
    {
#ifdef _DEBUG
        PyErr_Print();
#endif //_DEBUG
        throw server_config_exception("");
    }
}

void embedding_python_api::py_class_instance( const std::string &class_name )
{
    assert( pModule );
    if( pModule )
    {
        PyObject *pDict = PyModule_GetDict( pModule );
        if( pDict )
        {
            assert( !class_name.empty( ));
            //Получение по имени узказатель на класс из модуля python
            PyObject *pClass = PyDict_GetItemString( pDict,class_name.c_str( ));
            if( pClass )
            {
                if( PyCallable_Check( pClass ))
                {
                    pInstance = PyObject_CallObject( pClass, nullptr );
                }
                else
                {
#ifdef _DEBUG
                    PyErr_Print();
#endif //_DUBUG
                    throw std::logic_error( "Can not instance class:" + class_name );
                }
            }
            else
            {
#ifndef _DUBUG
                PyErr_Print();
#endif //_DEBUG
                throw std::logic_error( "Can not find class from python module: " + class_name );
            }
        }
    }
}
