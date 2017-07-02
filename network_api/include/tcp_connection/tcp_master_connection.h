#ifndef _TCP_MASTER_CONNECTION_H_
#define _TCP_MASTER_CONNECTION_H_

//internal
#include "connection_traits.h"
#include "master_connection.h"

namespace network
{
    class tcp_master_connection : public network::master_connection
    {
    public:
        explicit tcp_master_connection(endpoint_unique_ptr&);

        ~tcp_master_connection() override;

        void create_connection() override;

        void connect() noexcept;

        void set_timeout(const connection_timeout& t) override;

        void set_reusaddr() override;

        void set_nonblock() override;

        bool is_connection_nonblock() const;

        tcp_master_connection
          (const tcp_master_connection& other) = delete;

        tcp_master_connection& operator=
          (const tcp_master_connection& other) = delete;

        tcp_master_connection(tcp_master_connection&& other);

        tcp_master_connection& operator=(tcp_master_connection&& other);

    private:
        tcp_master_connection();

    private:
        class impl;
        std::unique_ptr<impl> d_;
    };

} //namespace

#endif //_TCP_MASTER_CONNECTION_H_
