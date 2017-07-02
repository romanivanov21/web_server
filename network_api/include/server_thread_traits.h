#ifndef _SERVER_THREAD_TRAITS_H_
#define _SERVER_THREAD_TRAITS_H_

#include "connection_traits.h"
#include "thread_save_queue.h"

#include <memory>
#include <vector>

namespace network
{
    class base_server_thread;
    using base_server_thread_unique_ptr = std::unique_ptr<base_server_thread>;
    using base_server_thread_shared_ptr = std::shared_ptr<base_server_thread>;
    using base_server_thread_weak_ptr = std::weak_ptr<base_server_thread>;
    using server_thread_poll = std::vector<base_server_thread_unique_ptr>;

    using slave_connection_queue = thread_save_queue<slave_connection_shared_ptr>;
    using slave_connection_queue_ptr = std::shared_ptr<slave_connection_queue>;
}

#endif //_SERVER_THREAD_THRAITS_H_