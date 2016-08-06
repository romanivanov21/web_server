/**
 *  Файл: delegete_base.h
 *
 *  Описание: Базовый класс реализации delegete
 */

#ifndef _DELEGATE_BASE_H_
#define _DELEGATE_BASE_H_

class delegate_base
{
public:
    delegate_base() = default;
    ~delegate_base() = default;

    delegate_base( const delegate_base& copy ) = delete;
    delegate_base& operator=( const delegate_base& copy ) = delete;
};

#endif //_DELEGATE_BASE_H_