/**
 *  Файл: error_log.h
 *
 *  Описание: Реализация логгирования ошибок
 */

#ifndef _ERROR_LOG_H_
#define _ERROR_LOG_H_

#include "server_log.h"

class error_log : public server_log
{
public:

    ~error_log() = default;

    /**
     * @brief инстансирование единосвенного экземпляра класса singleton
     *
     * @return ссылка на единственный экземпляр класса error_log
     */
    static error_log& get_instance() noexcept;

    /**
     * @brief сохранение записи в лог
     *
     * @param msg запись
     */
    void save_log( const std::string& msg ) override;

    error_log( const error_log& copy ) = delete;
    error_log& operator=( const error_log& copy ) = delete;

protected:
    /**
     * @brief создания структуры записи( время записи, сообщение и т. д. ) в лог
     *
     * @return формированное сообщение
     */
    const std::string& create_log_struct( const std::string &msg ) noexcept override;

private:
    error_log() = default;
};

#endif //_ERROR_LOG_H_