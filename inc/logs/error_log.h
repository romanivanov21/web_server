/**
 *  Файл: error_log.h
 *
 *  Описание: Реализация логгирования ошибок
 */

#ifndef _ERROR_LOG_H_
#define _ERROR_LOG_H_

#include "server_log.h"
#include "destroyer_singleton.h"

class error_log : public server_log
{
public:
    /**
     * @brief инстансирование единосвенного экземпляра класса singleton
     *
     * @return указатель на единственный экземпляр класса error_log
     */
    static error_log * get_instance() noexcept;

    void init_log_file( const std::string & file_name ) override;
    void save_log( const std::string & msg ) override;

    error_log(const error_log & copy) = delete;
    error_log & operator=(const error_log & copy) = delete;

private:
    error_log() = default;
    ~error_log()= default;

    static error_log * log;
    static destroyer_singleton<error_log> destroyer;

    friend class destroyer_singleton<error_log>;

private:
    std::string log_filename_;
};

#endif //_ERROR_LOG_H_