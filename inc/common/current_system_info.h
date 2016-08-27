/**
 *   Файл: current_system_info.h
 *
 *   Описание: класс для получения информации о системе
 */

#ifndef _CURRENT_SYSTEM_INFO_H_
#define _CURRENT_SYSTEM_INFO_H_

#include <string>

class current_system_info
{
 public:
    current_system_info() = default;
    ~current_system_info() = default;

    /**
     * @brief получение чила ядер процессора
     *
     * @return число ядер процессора
     */
    static size_t get_proc_kernel_count() noexcept;

    /**
     * @brief возвращает текущую директорию исполняемого файла
     *
     * @return теущая директория
     */
    static const std::string get_current_path() noexcept;

    current_system_info( const current_system_info &copy ) = delete;
    current_system_info& operator=( const current_system_info &copy ) = delete;
};

#endif //_CURRENT_SYSTEM_INFO_H_