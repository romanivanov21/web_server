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
            Py_DECREF( pValue );
        }
    }
    else
    {
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
            Py_DECREF( pValue );
        }
    }
    else
    {
#ifdef _DEBUG
        PyErr_Print();
#endif // _DEBUG
        throw std::logic_error("Class didn't instanced");
    }
}

#endif //_EMBEDDING_PYTHON_API_IMPL_H_