/**
 *  Файл: embedding_python_api.h
 *
 *  Описание: программный интерфейс для встраиваении программного
 *            кода на языке python ( основан на идиомие RAII )
 */

#ifndef _EMBEDDING_PYTHON_API_H_
#define _EMBEDDING_PYTHON_API_H_

#include <python2.7/Python.h>
#include <string>

class embedding_python_api
{
public:
    /**
     * @param module_name имя модуля python
     */
    embedding_python_api();
    ~embedding_python_api();

    /**
     * @brief импорт вызываемого python модуля
     *
     * @param module_name имя модуля
     */
    void py_module_import( const std::string& module_name );

    /**
     * @brief вызов функции из модуля python
     *
     * @param function_name имя функции из модуля python
     */
    void py_function_call( const std::string& function_name );

    embedding_python_api( const embedding_python_api& copy ) = delete;
    embedding_python_api& operator=( const embedding_python_api& copy ) = delete;

private:
    PyObject *pName_;
    PyObject *pModule_;
    PyObject *pFunc_;
};

#endif //_EMBEDDING_PYTHON_API_H_