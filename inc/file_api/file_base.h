/**
 *  Файл: file_base.h
 *
 *  Описание: интерфейс для работы с файловым вводом выводом,
 *            конкретная реализация ввода вывода ( например ввод-вывод OC Linux, буфферезированный ввод вывод
 *            стандарной билиотеки), должен реализовать данный интерфейс
 *
 *  Автор: Иванов Роман Витальевич (с)
 *
 */

#ifndef _FILE_BASE_H_
#define _FILE_BASE_H_

#include <string>
#include <vector>

typedef char byte;

class file_base
{
public:
    file_base() = default;

    virtual ~file_base() = default;

    virtual int get_char() noexcept = 0;

    virtual void read_line( std::string& str ) noexcept = 0;

    virtual void write_line( const std::string& str ) noexcept = 0;

    file_base( const file_base& copy ) = delete;

    file_base& operator=( const file_base& copy ) = delete;

    file_base( file_base&& other ) = default;

    file_base& operator=( file_base&& other ) = default;
};

#endif //_FILE_BASE_H_