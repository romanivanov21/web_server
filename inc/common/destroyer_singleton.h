/**
 *  Файл: destroyer_singleton.h
 *
 *  Описание: Файл для объявления класса destroyer_singleton, реализующий идиому RAII для класса singletone
 */

#ifndef _DESTROYER_SINGLETON_H_
#define _DESTROYER_SINGLETON_H_

template <typename T>
class destroyer_singleton
{
public:
    ~destroyer_singleton();
    void initialize(T* p);
private:
    T* pdestroy;
};

template <typename T>
destroyer_singleton<T>::~destroyer_singleton()
{
    delete pdestroy;
}

template <typename T>
void destroyer_singleton<T>::initialize(T * p)
{
    pdestroy = p;
}

#endif //_DESTROYER_SINGLETON_H_
