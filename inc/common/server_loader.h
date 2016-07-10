/**
 *  Файл: server_loader.h
 *
 *  Описание:
 */

#ifndef _SERVER_LOADER_H_
#define _SERVER_LOADER_H_

#include "master_loader.h"
#include "server_config.h"

class server_loader : public  master_loader
{
 public:
    server_loader( );
    ~server_loader( );

    void get_config( CONFIG_TYPES *cfg_type ) override;

 private:
    server_config *cfg_;
};

#endif //_SERVER_LOADER_H_