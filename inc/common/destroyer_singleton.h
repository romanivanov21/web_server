/**
 *  Файл: types.h
 *
 *  Описание: Файл для объявления общих типов и структур
 */

#ifndef _DESTROYER_SINGLETON_H_
#define _DESTROYER_SINGLETON_H_

template <typename T>
class destroyer_singleton
{
private:
    T * pdestroy;
public:
    ~destroyer_singleton();
    void initialize( T * p );
};

template <typename T>
destroyer_singleton<T>::~destroyer_singleton()
{
    delete pdestroy;
}

template <typename T>
void destroyer_singleton<T>::initialize( T * p )
{
    pdestroy = p;
}

#endif //_DESTROYER_SINGLETON_H_
