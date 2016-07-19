/**
 * Флайл: process_creator.h
 *
 * Описание:
*/

#ifndef _PROCESS_CREATOR_H_
#define _PROCESS_CREATOR_H_

#include "process.h"

class process_creator
{
 public:
    process_creator() { }
    virtual ~process_creator() { }

    virtual process* get_process() noexcept = 0;

    process_creator( const process_creator &copy ) = delete;
    process_creator& operator=( const process_creator &copy ) = delete;
};

#endif //_PROCESS_CREATOR_H_