/**
 *   Файл: singleton_destroyer.h
 *
 *   Опиасние: базовый класс для реализации паттерна синглтон,
 *             который предназначен для автоматического освобождения объекта
 */
#ifndef _SINGLETON_DESTROYER_H_
#define _SINGLETON_DESTROYER_H_

template <class T>
class singleton_destroyer
{
public:
    singleton_destroyer() = default;
    ~singleton_destroyer();

    void init_obj( T* obj ) noexcept;
    T* get_obj() const noexcept;

    singleton_destroyer( const singleton_destroyer& copy ) = delete;
    singleton_destroyer& operator= ( const singleton_destroyer& copy ) = delete;

private:
    T *obj_;
};
#include "singleton_destroyer_impl.h"
#endif //_SINGLETHON_DESTROYER_H_