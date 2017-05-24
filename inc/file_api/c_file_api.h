/**
 *  Файл: c_file_api.h
 *
 *  Описание: реализация класса, который инкапсулирует
 *            буферезировнный ввод вывод из библиотеки glibc
 *            реализуе базовый интерфайс работы с фалами file_base
 */

#ifndef _C_FILE_API_H_
#define _C_FILE_API_H_

#include "file_base.h"

#include "stdio.h"
#include <string>
#include <vector>
#include <cassert>

class c_file_api : public file_base
{
public:
    c_file_api( const std::string& filename, const std::string& mode );

    ~c_file_api();

    std::int64_t read_str( std::string& str ) const;

    size_t read_bytes_begin( size_t begin, std::string& str );

    int get_char() noexcept final;

    void read_line( std::string& str ) noexcept final;

    void write_line( const std::string& str ) noexcept final;

    c_file_api( const c_file_api& copy ) = delete;

    c_file_api& operator=( const c_file_api& copy ) = delete;

    c_file_api( c_file_api&& other );

    c_file_api& operator=( c_file_api&& other );

private:
    c_file_api( FILE* handle );

private:
    FILE* handle_;
};
#endif //_FILE_IO_H_