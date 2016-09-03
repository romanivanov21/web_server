/**
 *    Файл: singleton_destroyer_impl.h
 *
 *    Описние:
 */

#ifndef _SINGLETON_DESTROYER_IMPL_H_
#define _SINGLETON_DESTROYER_IMPL_H_

#include "singleton_destroyer.h"

#include <cassert>

template <class T>
singleton_destroyer<T>::~singleton_destroyer()
{
    delete obj_;
}

template <class T>
void singleton_destroyer<T>::init_obj( T *obj ) noexcept
{
    assert( obj != nullptr );

    obj_ = obj;
}

template <class T>
T* singleton_destroyer<T>::get_obj() const noexcept
{
    return obj_;
}
#endif //_SINGLETHON_DESTOYRET_IMPL_H_