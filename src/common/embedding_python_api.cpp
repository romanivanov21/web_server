#include "embedding_pyhton_api.h"

#include <cassert>

embedding_python_api::embedding_python_api() : pName_( nullptr ), pModule_( nullptr ), pFunc_( nullptr )
{
    Py_Initialize();
}

embedding_python_api::~embedding_python_api() noexcept
{
    if( pModule_ )
        Py_DECREF( pModule_ );
    if( pName_ )
        Py_DECREF( pName_ );

    Py_Finalize();
}

void embedding_python_api::py_module_import( const std::string &module_name )
{
    assert( !module_name.empty() );

    pName_ = PyString_FromString( module_name.c_str() );

    pModule_ = PyImport_Import( pName_ );
}

void embedding_python_api::py_function_call( const std::string &function_name )
{
    assert( !function_name.empty() );
    assert( pModule_ != nullptr );

    if( pModule_ != nullptr )
    {
        pFunc_ = PyObject_GetAttrString( pModule_, function_name.c_str() );
        if( pFunc_ != nullptr )
        {
            PyObject_CallObject( pFunc_, NULL );
        }
    }
}