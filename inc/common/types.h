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

#endif //_TYPES_H_
