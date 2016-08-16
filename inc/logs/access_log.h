/**
 *  Файл: access_log.h
 *
 *  Описание: Реализация логгирования успешно выполненных действий
 */

#ifndef _ACCESS_LOG_H_
#define _ACCESS_LOG_H_

#include "server_log.h"

class access_log;

class destroyer_access_log
{
private:
    access_log * log;
public:
    ~destroyer_access_log();
    void initialize( access_log * p );
};

class access_log : public server_log
{
public:
    /**
     * @brief инстансирование единосвенного экземпляра класса singleton
     *
     * @return указатель на единственный экземпляр класса access_log
     */
    static access_log * get_instance() noexcept;

    void init_log_file( const std::string & file_name ) override;
    void save_log( const std::string & msg ) override;

    access_log(const access_log & copy) = delete;
    access_log & operator=(const access_log & copy) = delete;

private:
    access_log() = default;
    ~access_log()= default;

    static access_log * log;
    static destroyer_access_log destroyer;

    friend class destroyer_access_log;
};

#endif //_ACCESS_LOG_H_