#include "listen_thread.h"
#include "master_connection.h"
#include "selector_traits.h"
#include "selector_epoll.h"
#include "tcp_master_connection.h"
#include "tcp_slave_connection.h"
#include "joinable_thread.h"
#include "base_network_error.h"

using namespace network;

struct listen_thread::impl
{
    slave_connection_queue_ptr connection_queue_ = nullptr;
    base_selector_unique_ptr selector_ = nullptr;
    master_connection_unique_ptr server_connection_ = nullptr;
    joinable_thread_unique_ptr thread_ = nullptr;

    void on_connected(const network::slave_connection_shared_ptr& client);

    void on_connection_error(const network::connection_error& error);

    void on_disconnected();
};

listen_thread::listen_thread(endpoint_unique_ptr& ep,
 slave_connection_queue_ptr& connection_queue) : d_(std::make_unique<impl>())
{
    if(d_)
    {
        d_->connection_queue_ = connection_queue;
        d_->selector_ = std::unique_ptr<selector_epoll>();
        d_->server_connection_ = std::make_unique<tcp_master_connection>(ep);
        d_->thread_ = std::make_unique<joinable_thread>
          (std::bind(&listen_thread::start, this));

        d_->server_connection_->connected_callback
          (std::bind(&listen_thread::impl::on_connected, d_.get(), std::placeholders::_1));
        d_->server_connection_->error_callback
          (std::bind(&listen_thread::impl::on_connection_error, d_.get(), std::placeholders::_1));
        d_->server_connection_->disconnected_callback
          (std::bind(&listen_thread::impl::on_disconnected, d_.get()));
    }
}

listen_thread::~listen_thread() noexcept = default;

void listen_thread::start() noexcept
{
    d_->server_connection_->create_connection();

    while(1)
    {
        d_->server_connection_->connect();
    }
}

void listen_thread::impl::on_connected
  (const network::slave_connection_shared_ptr& client)
{
    connection_queue_->push(client);
}

void listen_thread::impl::on_connection_error
  (const network::connection_error& error)
{

}

void listen_thread::impl::on_disconnected()
{

}
