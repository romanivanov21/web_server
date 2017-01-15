#include "master_process.h"
#include "connection.h"
#include "tcp_connection_creator.h"
#include "endpoint_ipv4.h"
#include "endpoint_ipv6.h"
#include "connection_except.h"
#include "server_config.h"
#include "access_log.h"
#include "error_log.h"

#include <cstring>

void master_process::start_process() noexcept
{
    ///!TODO: функция работает в тестовом режиме
    const config_struct* cfg = server_config::get_instance()->get_config();
    assert( cfg );
    if( cfg )
    {
        std::unique_ptr<endpoint> server_endpoint = nullptr;
        std::unique_ptr<endpoint> client_endpoint = nullptr;
        const std::string ip_address = cfg->server_.connection_.ip_address_;
        const size_t port = cfg->server_.connection_.listen_;
        if( cfg->server_.connection_.ip_version_ == config_server::server_connection::CONFIG_IPv4 )
        {
            server_endpoint = std::make_unique<endpoint_ipv4>( ip_address, port );
            client_endpoint = std::make_unique<endpoint_ipv4>();
        }
        else if( cfg->server_.connection_.ip_version_ == config_server::server_connection::CONFIG_IPv6 )
        {
            server_endpoint = std::make_unique<endpoint_ipv6>( ip_address, port );
            client_endpoint = std::make_unique<endpoint_ipv6>();
        }

        try
        {
            assert( server_endpoint.get() );
            if( server_endpoint.get() )
            {
                std::unique_ptr<connection_creator> creator = std::make_unique<tcp_connection_creator>( std::move( server_endpoint ) );
                creator->set_reusaddr();
                assert( creator.get() );
                if( creator.get() )
                {
                    assert( client_endpoint.get() );
                    if( client_endpoint.get() )
                    {
                        std::unique_ptr<connection> connect = std::move( creator->get_connection( client_endpoint ) );
                        access_log::get_instance()->save_log( "Connected new client ip address: " + client_endpoint->get_ip_address() );
                        assert( connect.get() );
                        if( connect.get() )
                        {
                            std::string str( 10, 0 );
                            connect->receive_data( str );
                            connect->send_data( str );
                        }
                        else
                        {
                            error_log::get_instance()->save_log( "System error while to open connection" );
                        }
                    }
                    else
                    {
                        error_log::get_instance()->save_log( "System error while to open connection" );
                    }
                }
                else
                {
                    error_log::get_instance()->save_log( "System error while to open connection" );
                }
            }
            else
            {
                error_log::get_instance()->save_log( "System error while to open connection" );
            }
        }
        catch( const connection_except& ex )
        {
            error_log::get_instance()->save_log( ex.what() );
        }
        catch( ... )
        {
            error_log::get_instance()->save_log( "Unknown error create new connection" );
        }
    }
}