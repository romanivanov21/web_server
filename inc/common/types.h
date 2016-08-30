/**
 *  Файл: types.h
 *
 *  Описание: Файл для объявления общих типов и структур
 */

#ifndef _TYPES_H_
#define _TYPES_H_

#include <cassert>
#include <string>

/* Ошибка по умолчанию */
static const int default_error_code = -1;

/* Максимальное число tcp портов */
static const std::uint32_t tcp_port_max = 65535;

enum state_process { CHILD_PROCESS = 0, ERROR_PROCESS = -1 };

static const std::string dell_last_dir( std::string& path )
{
    assert( !path.empty() );

    size_t found = path.rfind( '/' );
    if( found != std::string::npos )
        path.erase( found );
    return path;
}

static void add_dir ( std::string& dir, const std::string& value )
{
    assert( !dir.empty() );

    dir += "/";
    dir += value;
}

#endif //_TYPES_H_
