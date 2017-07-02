#ifndef _BASE_SERVER_THREAD_H_
#define _BASE_SERVER_THREAD_H_

//internal
#include "base_network_error.h"
#include "event.h"

//std
#include <functional>

namespace network
{
    class base_server_thread
    {
    public:
        using error_callback_function =
            std::function<void(const base_network_error&)>;

        base_server_thread() = default;

        virtual ~base_server_thread() noexcept = default;

        virtual void start() noexcept = 0;

    protected:
        event<const base_network_error&> error;
    };
}

#endif //_BASE_SERVER_THREADS_H_