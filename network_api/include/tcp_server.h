#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

//internal
#include "base_server.h"
#include "selector_traits.h"
#include "connection_traits.h"
#include "joinable_thread.h"
#include "user_session_traits.h"

namespace network
{
    class tcp_server : public base_server
    {
    public:
        tcp_server(base_selector_unique_ptr&,
           endpoint_unique_ptr&,
           base_user_session_ptr&,
           std::size_t worker_thread_count
           = joinable_thread::hardware_concurrency());

        ~tcp_server() noexcept override;

        void run() noexcept override;

        tcp_server(const tcp_server& other) = delete;
        tcp_server& operator=(const tcp_server& other) = delete;

    private:
        struct impl;
        std::unique_ptr<impl> d_;
    };

} //namespace

#endif //_TCP_SERVER_H_
