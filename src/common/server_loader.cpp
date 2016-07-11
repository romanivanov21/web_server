/**
 *  Файл: server_loader.h
 *
 *  Описание:
 */

#include "master_loader.h"
#include "server_loader.h"

#include "server_config_exception.h"

#include <cassert>

server_loader::server_loader(  connection *connection ) : cfg_( server_config::get_instance() ), connenct_( connection )
{
    assert( connection );
}

server_loader::~server_loader( ) { }

const CONFIG_TYPES* server_loader::get_config( )
{
    try
    {
        cfg_.load_cfg_file( "/home/.." );
    }
    catch( const server_config_exception& ex )
    {
        throw ex;
    }
    ///TDD: функция не реализована
    throw;
    return cfg_.get_config();
}
