#ifndef _UDP_CONNECTION_H_
#define _UDP_CONNECTION_H_

//internal
#include "slave_connection.h"
#include "connection_creator.h"

namespace network
{
    class udp_connection : public connection
    {
    public:
        explicit udp_connection(std::unique_ptr<connection_creator::io_service> io_service);

        ~udp_connection();

    private:
        std::unique_ptr<>
    };

} //network

#endif //_UDP_CONNECTION_H_