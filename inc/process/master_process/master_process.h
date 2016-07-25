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
    master_process();
    ~master_process();

    void start_process() noexcept override;
    void set_config() noexcept;
    static void sighandler(int signum);

    master_process( const master_process &copy ) = delete;
    master_process& operator=( const master_process &copy ) = delete;

private:
    process_manager *manager_;
};

#endif //_MASTER_PROCESS_H_