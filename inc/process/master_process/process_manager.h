/**
 * Флайл: process_manager.h
 *
 * Описание:
 */

#ifndef _PROCESS_MANAGER_H_
#define _PROCESS_MANAGER_H_

class process_manager
{
public:
    process_manager() { }
    ~process_manager() { }

    process_manager( const process_manager &copy ) = delete;
    process_manager& operator=( const process_manager &copy ) = delete;
};
#endif //_PROCESS_MANAGER_H_