/**
 *  Файл: master_loader.h
 *
 *  Описание:
 */

#ifndef _MASTER_LOADER_H_
#define _MASTER_LOADER_H_

#include "types.h"

class master_loader
{
 public:
    master_loader( ) { }
    virtual ~master_loader( ) { }

    virtual const CONFIG_TYPES* get_config( ) = 0;

    master_loader( const master_loader &copy ) = delete;
    master_loader& operator=( const master_loader &copy ) = delete;
};
#endif //_MASTER_LOADER_H_