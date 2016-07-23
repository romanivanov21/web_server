/**
 * Флайл: master_process.h
 *
 * Описание:
 */

#include "process_manager.h"
#include "process.h"

#ifndef _MASTER_PROCESS_H_
#define _MASTER_PROCESS_H_

class master_process : public process
{
public:
    ~master_process();

    void start_process() noexcept override;
    void set_config() noexcept;

    static master_process* get_instance() noexcept;

    master_process( const master_process &copy ) = delete;
    master_process& operator=( const master_process &copy ) = delete;

private:
    master_process();
private:
    process_manager *manager_;
};

#endif //_MASTER_PROCESS_H_