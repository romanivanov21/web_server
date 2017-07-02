#ifndef _SERVER_TRAITS_H_
#define _SERVER_TRAITS_H_

#include <memory>

namespace network
{
    class base_server;
    using base_server_unique_ptr = std::unique_ptr<base_server>;

    class tcp_server;
    using tcp_server_unique_ptr = std::unique_ptr<tcp_server>;
}

#endif //_SERVER_TRAITS_H_