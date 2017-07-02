#ifndef _CONNECTION_TRAITS_H_
#define _CONNECTION_TRAITS_H_

//std
#include <memory>

namespace network
{
    const int default_error_code = -1;

    using connection_port = std::uint16_t;

    class endpoint;
    using endpoint_unique_ptr = std::unique_ptr<endpoint>;
    using endpoint_shared_ptr = std::shared_ptr<endpoint>;
    using endpoint_weak_ptr = std::weak_ptr<endpoint>;

    class master_connection;
    using master_connection_unique_ptr = std::unique_ptr<master_connection>;
    using master_connection_shared_ptr = std::shared_ptr<master_connection>;
    using master_connection_weak_ptr = std::weak_ptr<master_connection>;

    class slave_connection;
    using slave_connection_unique_ptr = std::unique_ptr<slave_connection>;
    using slave_connection_shared_ptr = std::shared_ptr<slave_connection>;
    using slave_connection_weak_ptr = std::weak_ptr<slave_connection>;

    class connection_error;
}

#endif //_CONNECTION_TRAITS_H_