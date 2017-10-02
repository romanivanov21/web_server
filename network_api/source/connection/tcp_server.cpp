//internal
#include "tcp_server.h"
#include "tcp_master_connection.h"
#include "base_server_thread.h"
#include "server_thread_traits.h"
#include "worker_thread.h"
#include "listen_thread.h"
#include "base_selector.h"
#include "base_server_thread.h"

using namespace network;

struct tcp_server::impl
{
    impl(endpoint_unique_ptr& ep);

    ~impl();

    // Пулл потоково сервера
    server_thread_poll thread_poll_;
    // Число worker потоков
    std::size_t worker_threads_count = 0;
    // Очередь входящих соединений
    slave_connection_queue_ptr connection_queue_ = nullptr;
    // Информация о сетевом соедение сервера
    endpoint_unique_ptr& ep_;
};

tcp_server::impl::impl(endpoint_unique_ptr& ep) : ep_(ep) { }

tcp_server::impl::~impl() = default;

/*tcp_server::tcp_server
  (base_selector_unique_ptr& selector, endpoint_unique_ptr& ep,
   base_user_session_ptr& session,
   std::size_t worker_thread_count) : d_(std::make_unique<impl>(ep))
{
    assert(selector && ep && session && worker_thread_count > 0);
    if(d_)
    {
        d_->worker_threads_count = worker_thread_count;
        d_->connection_queue_ = std::make_shared<slave_connection_queue>();
    }
}*/

//tcp_server::tcp_server(const tcp_server& other) = delete;

//tcp_server& tcp_server::operator=(const tcp_server& other) = delete;

tcp_server::~tcp_server() = default;

void tcp_server::run() noexcept
{
    if(!d_ || !d_->connection_queue_) 
        error.emit({base_network_error::network_error_type::
                    memory_allocate_error}); return;

    base_server_thread_unique_ptr listen_thread_ptr =
      std::make_unique<listen_thread>(d_->ep_, d_->connection_queue_);
    if(!listen_thread_ptr)
    {
        error.emit({base_network_error::network_error_type::
                    memory_allocate_error}); return;
    }

    d_->thread_poll_.push_back(std::move(listen_thread_ptr));

    for(auto i = 0; i < d_->worker_threads_count; i++)
    {
        base_server_thread_unique_ptr worker_thread_ptr =
          std::make_unique<network::worker_thread>(d_->connection_queue_);
        if(!worker_thread_ptr)
        {
            error.emit({base_network_error::network_error_type::
                        memory_allocate_error}); return;
        }
        d_->thread_poll_.push_back(std::move(worker_thread_ptr));
    }
}
