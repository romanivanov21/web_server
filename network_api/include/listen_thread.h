#ifndef _LISTEN_THREAD_H_
#define _LISTEN_THREAD_H_

//Internal
#include "listen_thread.h"
#include "base_server_thread.h"
#include "server_thread_traits.h"
#include "connection_traits.h"

namespace network
{
    class listen_thread : public base_server_thread
    {
    public:
        listen_thread
          (endpoint_unique_ptr& ep,
           slave_connection_queue_ptr& connection_queue);

        ~listen_thread() noexcept override;

        void start() noexcept final;

    private:
        struct impl;
        std::unique_ptr<impl> d_;
    };

} //namespace

#endif //_LISTEN_THREAD_H_