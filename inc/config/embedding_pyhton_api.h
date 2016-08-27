/**
 *  Файл: embedding_python_api.h
 *
 *  Описание: программный интерфейс для встраиваении программного
 *            модуля config_parser на языке python ( основан на идиомие RAII )
 */

#ifndef _EMBEDDING_PYTHON_API_H_
#define _EMBEDDING_PYTHON_API_H_

#include <python2.7/Python.h>
#include <vector>
#include <string>
#include <stdexcept>

class embedding_python_api
{
public:
    embedding_python_api();
    ~embedding_python_api();

    /**
     * @brief установка и настройка дректорий до python модулей
     *
     * @param module_patch директория до python модуля
     */
    void py_set_module_path( const std::string& module_patch ) noexcept;

    /**
     * @brief импорт используемого python модуля
     *
     * @param module_name имя импортируемого модуля
     *
     * @throw 
     */
    void py_import_module( const std::string& module_name );

    /**
     * @brief вызов функции из модуля python
     *
     * @param function_name имя функции из модуля python
     * @param format формат параметров вызываемой функции
     */
    void py_function_call( const std::string& function_name, char *format, ... );

    /**
     *  @brief создания экземпляра класса из модуля python
     *
     *  @param class_name имя класса из модуля python
     *
     *  @throw std::logic_error
     */
    void py_class_instance( const std::string& class_name );

    template <class... Args>
    void py_class_method_call( const std::string& method_name, bool& ret_value, char* format, Args... args )
    {
        assert( !method_name.empty() );

        PyObject* pValue = nullptr;
        PyObject* pMethod = PyObject_GetAttrString( pInstance, method_name.c_str() );
        if( ( pInstance ) && ( PyCallable_Check( pMethod ) ) )
        {
            pValue = PyObject_CallMethod( pInstance, const_cast<char *>(method_name.c_str()), format, args... );
            if( pValue )
            {
                ret_value = static_cast<bool >( pValue );
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

    /**
     *  @brief вызов метода из модуля python
     */
    template <class... Args>
    void py_class_method_call( const std::string& method_name, const char **ret_buffer, char *format, Args... args )
    {
        assert( !method_name.empty() );

        PyObject* pValue = nullptr;
        PyObject* pMethod = PyObject_GetAttrString( pInstance, method_name.c_str() );
        if( ( pInstance ) && ( PyCallable_Check( pMethod ) ) )
        {
            pValue = PyObject_CallMethod( pInstance, const_cast<char *>(method_name.c_str()), format, args... );
            if( ( pValue ) && ( ret_buffer ) )
            {
                PyObject_AsCharBuffer( pValue, ret_buffer, &pValue->ob_refcnt );
                PyErr_Print();
                Py_DECREF( pValue );
            }
        }
        else
        {
#ifdef _DEBUG
            PyErr_Print();
#endif //_DEBUG
            throw std::logic_error("Class didn't instanced");
        }
    }

    embedding_python_api( const embedding_python_api& copy ) = delete;
    embedding_python_api& operator=( const embedding_python_api& copy ) = delete;

private:
    PyObject *pInstance;
    PyObject *pName;
    PyObject *pModule;
};

#endif //_EMBEDDING_PYTHON_API_H_