#include "current_system_info.h"

#ifdef __linux__
#include <linux/limits.h>
#include <zconf.h>
#else
#include <windows.h>
#endif //__linux__

#include <cstring>

size_t current_system_info::get_proc_kernel_count() noexcept
{
    //!TDD необходимо реализовать функцию для получения числа ядер процессора
    return 4;
}

const std::string current_system_info::get_current_path() noexcept
{
#ifdef __linux__
    char buff[ PATH_MAX + 1 ];
    std::memset( buff, 0x00, PATH_MAX + 1 );
    ssize_t len = readlink( "/proc/self/exe", buff, PATH_MAX );
    buff[len] = 0;
#else
    char buff[ _MAX_PATH ];
    std::memset( buff, 0x00, _MAX_PATH );
    GetModuleFileNmae( NULL, &res[0], _MAX_PATH );
#endif //__linux__
    return std::string( buff );
}