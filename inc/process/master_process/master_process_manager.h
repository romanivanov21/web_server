/**
 * Флайл: master_process_manager.h
 *
 * Описание:
 */

#include "process_manager.h"

#ifndef _MASTER_PROCESS_MANAGER_H_
#define _MASTER_PROCESS_MANAGER_H_

class master_process_manager : public process_manager
{
public:
    master_process_manager();
    ~master_process_manager();

    master_process_manager( const master_process_manager &copy )  = delete;
    master_process_manager& operator=( const master_process_manager &copy ) = delete;
};
#endif //_MASTER_PROCESS_MANAGER_H_