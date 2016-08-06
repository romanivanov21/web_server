/**
 *  Файл: access_error.h
 *
 *  Описание: Реализация логгирования успешно выполненных действий
 */

#include "server_log.h"

class access_log : public server_log
{
 public:
    ~access_log() = default;

    /**
     * @brief инстансирование единосвенного экземпляра класса singleton
     *
     * @return сылка на единственный экземпляр класса access_log
     */
    static access_log& get_instance() noexcept;

    void save_log( const std::string& msg ) override;

    access_log( const access_log &copy ) = delete;
    access_log& operator=( const access_log &copy ) = delete;

protected:
    /**
     * @brief создания структуры записи( время записи, сообщение и т. д. ) в лог
     *
     * @return формированное сообщение
     */
    const std::string& create_log_struct( const std::string &msg ) noexcept override;
private:
    access_log() = default;
};