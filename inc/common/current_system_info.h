/**
 *   Файл: current_system_info.h
 *
 *   Описание: класс для получения информации о системе
 */

#ifndef _CURRENT_SYSTEM_INFO_H_
#define _CURRENT_SYSTEM_INFO_H_

class current_system_info
{
 public:
    ~current_system_info() = default;

    /**
     * @brief инстанцирование объекта класса singleton
     *
     * @return объект класса в единственном экземпляре
     */
    static current_system_info& get_instance() noexcept;

    /**
     * @brief получение чила ядер процессора
     *
     * @return число ядер процессора
     */
    unsigned int get_proc_kernel_count() noexcept;

    current_system_info( const current_system_info &copy ) = delete;
    current_system_info& operator=( const current_system_info &copy ) = delete;
 private:
    current_system_info() = default;
};

#endif //_CURRENT_SYSTEM_INFO_H_