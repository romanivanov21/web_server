/**
 *  Файл: server_loader.h
 *
 *  Описание:
 */

#include "master_loader.h"
#include "server_loader.h"

#include <cassert>

server_loader::server_loader( ) : cfg_( server_config::get_instance() )
{
    assert( cfg_ );
}

server_loader::~server_loader( ) { }

void server_loader::get_config( CONFIG_TYPES *cfg_type )
{
    assert( cfg_type );
    ///TDD: функция не реализована
    throw;
}
