#include "current_system_info.h"

current_system_info::current_system_info( )
{
}

current_system_info::~current_system_info( )
{
}

current_system_info& current_system_info::get_instance( )
{
    static current_system_info system_info;
    return system_info;
}

unsigned int current_system_info::get_proc_kernel_count( )
{
    //!TDD необходимо реализовать функцию для получения числа ядер процессора
    return 4;
}