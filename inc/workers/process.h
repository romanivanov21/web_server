/**
 * Флайл: process.h
 *
 * Описание:
 */

#ifndef _PROCESS_H_
#define _PROCESS_H_

class process
{
 public:
    process() { }
    virtual ~process(){ }

    virtual bool start_process() = 0;

    process( const process &copy ) = delete;
    process& operator=( const process &copy ) = delete;
};
#endif //_PROCESS_H_