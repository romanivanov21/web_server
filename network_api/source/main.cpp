#include "connection_error.h"
#include "slave_connection.h"
#include "endpoint_ipv4.h"
#include "master_connection.h"
#include "tcp_master_connection.h"
#include "base_selector.h"
#include "selector_epoll.h"
#include "tcp_server.h"
#include "base_server.h"
#include "base_network_error.h"
#include "user_session_traits.h"
#include "server_traits.h"
#include "base_user_session.h"
#include "http_session.h"

#include <iostream>

/*class tcp_server
{
public:
    tcp_server()
      : selector_(std::make_unique<network::selector_epoll>()),
        ep_(std::make_unique<network::endpoint_ipv4>("127.0.0.1", 8000)),
        server_connection_(std::make_unique<network::tcp_master_connection>(ep_))
    {
        if(!server_connection_) return;

        // Подписка на события
        server_connection_->connected_callback
          (std::bind(&tcp_server::on_connected, this, std::placeholders::_1));

        server_connection_->error_callback
          (std::bind(&tcp_server::on_connection_error, this, std::placeholders::_1));

        server_connection_->timeout_callback
          (std::bind(&tcp_server::on_timeout, this));

        server_connection_->disconnected_callback
          (std::bind(&tcp_server::on_disconnected, this));

        selector_->data_ready_callback
          (std::bind(&tcp_server::on_received, this, std::placeholders::_1));

        selector_->error_callback
          (std::bind(&tcp_server::on_selector_error, this, std::placeholders::_1));

        // Установка флагов и опций
        server_connection_->set_reusaddr();
        server_connection_->set_nonblock();
    }

    void run()
    {
        while(1)
        {
            // Запуск соединения
            server_connection_->create_connection();
            selector_->check_data_ready(10, 1);
        }
    }

    void on_connected(const network::slave_connection_shared_ptr& client)
    {
        if(!client) return;
        selector_->add_connection(client);
    }

    void on_timeout()
    {
        std::cout << "timeout" << std::endl;
    }

    void on_disconnected()
    {
        std::cout << "disconnected" << std::endl;
    }

    void on_received(const network::slave_connection_shared_ptr& connection)
    {
        std::vector<byte> v;
        v.resize(10);
        connection->receive_data(v);
        std::cout << "received" << std::endl;
        for(const auto& item : v)
        {
            std::cout << item;
        }
        std::cout<<"\n";
        connection->send_data(v);
    }

    void on_connection_error(const network::connection_error& error)
    {
        std::cout << "error" << error.what() << std::endl;
    }

    void on_selector_error(const network::selector_error& error)
    {
        std::cout << "selector error" << static_cast<std::uint32_t>(error);
    }

private:
    network::base_selector_unique_ptr selector_;
    network::endpoint_unique_ptr ep_;
    network::master_connection_unique_ptr server_connection_;
};
*/

void on_server_error(const network::base_network_error& error)
{
    std::cout<<error.what()<<std::endl;
}

int main()
{
    network::endpoint_unique_ptr ep
      = std::make_unique<network::endpoint_ipv4>("127.0.0.1", 8080);
    network::base_selector_unique_ptr selector
      = std::make_unique<network::selector_epoll>();

    network::base_user_session_ptr session
      = std::make_unique<network::http_session>();
    network::tcp_server s(selector, ep, session);
    s.error_callback(&on_server_error);
    s.run();
    return 0;
}
