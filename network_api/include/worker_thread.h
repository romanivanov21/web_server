#ifndef _WORKER_THREAD_H_
#define _WORKER_THREAD_H_

#include "base_server_thread.h"
#include "server_thread_traits.h"

namespace network
{
    class worker_thread : public base_server_thread
    {
    public:
        worker_thread(slave_connection_queue_ptr& connection_queue);

        ~worker_thread() override;

        void start() noexcept final;

    private:
        struct impl;
        std::unique_ptr<impl> d_;
    };
}

#endif //_WORKER_THREAD_H_