#ifndef _CURRENT_SYSTEM_INFO_H_
#define _CURRENT_SYSTEM_INFO_H_

class current_system_info
{
 public:
    ~current_system_info();

    static current_system_info& get_instance();

    unsigned int get_proc_kernel_count();

    current_system_info( const current_system_info &copy ) = delete;
    current_system_info& operator=( const current_system_info &copy ) = delete;
 private:
    current_system_info();
};

#endif //_CURRENT_SYSTEM_INFO_H_