/**
 *  Файл: embedding_python_api.h
 *
 *  Описание: программный интерфейс для встраиваении программного
 *            модуля config_parser на языке python ( основан на идиомие RAII )
 */

#ifndef _EMBEDDING_PYTHON_API_H_
#define _EMBEDDING_PYTHON_API_H_

#include <python2.7/Python.h>
#include <string>

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

    embedding_python_api( const embedding_python_api& copy ) = delete;
    embedding_python_api& operator=( const embedding_python_api& copy ) = delete;

private:
    PyObject *pName;
    PyObject *pModule;
    PyObject *pFunc;
};

#endif //_EMBEDDING_PYTHON_API_H_