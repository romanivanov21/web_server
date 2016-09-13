#ifndef _EMBEDDING_PYTHON_API_IMPL_H_
#define _EMBEDDING_PYTHON_API_IMPL_H_

#include "embedding_pyhton_api.h"

#include <string>
#include <cassert>
#include <python2.7/Python.h>

template <class... Args>
void embedding_python_api::py_class_method_call( const std::string& method_name, bool& ret_value, char* format, Args... args )
{
    assert( !method_name.empty() );

    PyObject* pValue = nullptr;
    PyObject* pMethod = PyObject_GetAttrString( pInstance, method_name.c_str() );
    if( ( pInstance ) && ( PyCallable_Check( pMethod ) ) )
    {
        pValue = PyObject_CallMethod( pInstance, const_cast<char *>(method_name.c_str()), format, args... );
        if( pValue )
        {
            ret_value = static_cast<bool>( PyObject_IsTrue( pValue ) );
            Py_DECREF( pMethod );
            Py_DECREF( pValue );
        }
    }
    else
    {
        Py_DECREF( pMethod );
        Py_DECREF( pValue );
#ifdef _DEBUG
        PyErr_Print();
#endif // _DEBUG
        throw std::logic_error("Class didn't instanced");
    }
}

template <class... Args>
void embedding_python_api::py_class_method_call( const std::string &method_name, std::string& ret_value, char* format, Args... args )
{
    assert( !method_name.empty() );

    PyObject* pValue = nullptr;
    PyObject* pMethod = PyObject_GetAttrString( pInstance, method_name.c_str() );
    if( ( pInstance ) && ( PyCallable_Check( pMethod ) ) )
    {
        pValue = PyObject_CallMethod( pInstance, const_cast<char *>(method_name.c_str()), format, args... );
        if( pValue )
        {
            ret_value = PyString_AsString( pValue );
            Py_DECREF( pMethod );
            Py_DECREF( pValue );
        }
    }
    else
    {
        Py_DECREF( pValue );
        Py_DECREF( pMethod );
#ifdef _DEBUG
        PyErr_Print();
#endif // _DEBUG
        throw std::logic_error( "Class didn't instanced or py method name error" );
    }
}

template <class... Args >
void embedding_python_api::py_class_method_call( const std::string& method_name, std::map<std::string, std::string>& ret_value, char *args_format, Args... args )
{
    assert( !method_name.empty() );

    PyObject *pValue = nullptr;
    PyObject *pMethod = PyObject_GetAttrString( pInstance, method_name.c_str() );
    if( ( pInstance ) && ( PyCallable_Check( pMethod ) ) )
    {
        pValue = PyObject_CallMethod( pInstance, const_cast<char *>( method_name.c_str() ), args_format, args... );
        if( pValue )
        {
            PyObject *pKeys = PyDict_Keys( pValue );
            if( pKeys )
            {
                std::size_t len = PyList_Size( pKeys );

                PyObject *pKeyItem = nullptr;
                PyObject *pKey = nullptr;
                for( size_t i = 0 ; i < len ; i++ )
                {
                    pKeyItem = PyDict_GetItem( pValue,PyList_GetItem( pKeys,i ));
                    if( pKeyItem )
                    {
                        ret_value[std::string( PyString_AsString( PyList_GetItem( pKeys,i )))] = std::string( PyString_AsString( pKeyItem ));
                    }
                }
                Py_DECREF( pKeys );
                Py_DECREF( pKeyItem );
            }

            Py_DECREF( pMethod );
            Py_DECREF( pValue );
        }
    }
    else
    {
#ifdef _DEBUG
        PyErr_Print();
#endif //_DEBUG
        throw std::logic_error( "Class didn't instanced or py method name error" );
    }
}

#endif //_EMBEDDING_PYTHON_API_IMPL_H_