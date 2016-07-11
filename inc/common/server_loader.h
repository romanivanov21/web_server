/**
 *  Файл: server_loader.h
 *
 *  Описание:
 */

#ifndef _SERVER_LOADER_H_
#define _SERVER_LOADER_H_

#include "master_loader.h"
#include "server_config.h"
#include "connection.h"

#include <memory>

class server_loader : public  master_loader
{
 public:
    server_loader( connection *connect );
    ~server_loader( );

    const CONFIG_TYPES* get_config( ) override;

 private:
    server_config &cfg_;
    connection *connenct_;
};

#endif //_SERVER_LOADER_H_