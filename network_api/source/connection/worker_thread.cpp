#include "worker_thread.h"
#include "base_selector.h"
#include "selector_epoll.h"
#include "joinable_thread.h"

using namespace network;

struct worker_thread::impl
{
    slave_connection_queue_ptr connection_queue_ = nullptr;
    base_selector_unique_ptr selector_ = nullptr;
    joinable_thread_unique_ptr thread_ = nullptr;

    void on_data_ready(const network::slave_connection_shared_ptr& connection);

    void on_selector_error(const network::selector_error& error);
};

worker_thread::worker_thread(slave_connection_queue_ptr& connection_queue)
  : d_(std::make_unique<impl>())
{
    if(!d_ || !connection_queue) return;
    d_->connection_queue_ = connection_queue;

    d_->selector_ = std::make_unique<selector_epoll>();
    if(!d_->selector_) return;

    d_->selector_->data_ready_callback
      (std::bind(&worker_thread::impl::on_data_ready, d_.get(),
                 std::placeholders::_1));

    d_->selector_->error_callback
      (std::bind(&worker_thread::impl::on_selector_error, d_.get(),
                 std::placeholders::_1));

    d_->thread_ = std::make_unique<joinable_thread>
      (std::bind(&worker_thread::start, this));
}

worker_thread::~worker_thread()
{

}

void worker_thread::start() noexcept
{
    while(1)
    {
        slave_connection_shared_ptr connection;// = d_->connection_queue_->try_pop();
        if(connection)
        {
            d_->selector_->add_connection(connection);
        }
        d_->selector_->check_data_ready(100, 1);
    }
}

void worker_thread::impl::on_data_ready
  (const network::slave_connection_shared_ptr& connection)
{

}

void worker_thread::impl::on_selector_error
  (const network::selector_error& error)
{

}