/**
 *  Файл: access_log.h
 *
 *  Описание: Реализация логгирования успешно выполненных действий
 */

#ifndef _ACCESS_LOG_H_
#define _ACCESS_LOG_H_

#include "server_log.h"
#include "destroyer_singleton.h"

class access_log : public server_log
{
public:
    /**
     * @brief инстансирование единосвенного экземпляра класса singleton
     *
     * @return указатель на единственный экземпляр класса access_log
     */
    static access_log* get_instance() noexcept;

    access_log(const access_log& copy) = delete;
    access_log& operator=(const access_log& copy) = delete;

private:
    access_log() = default;
    ~access_log()= default;

    static access_log* log;
    static destroyer_singleton<access_log> destroyer;

    friend class destroyer_singleton<access_log>;
};

#endif //_ACCESS_LOG_H_