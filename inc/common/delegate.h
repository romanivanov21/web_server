/**
 *	Файл: delegate.h
 *
 *	Описание: Реализация делегата на основе std::function
 */

#ifndef _DELEGATE_H_
#define _DELEGATE_H_

#include "delegate_base.h"
#include "event.h"

#include <functional>

template <class T>
class delegate;

template <class... Args>
class delegate<void( Args... )> : public delegate_base
{
public:
    typedef std::function< void(Args...) > func;

public:
    /**
     * @param вызываемя функция
     */
    delegate( func f ) noexcept : f_( f ) { }
    ~delegate() = default;

    /**
     * @brief определние оператора (), чтобы
     *		  объект класса delegate являлся
     *		  функциональным объектом
     *
     * @param аргументы вызываемой функции
     */
    virtual void operator() ( Args... args ) {  f_( args ... ); }

private:
    func f_;
};

#endif //_DELEGATE_H_