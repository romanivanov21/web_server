#ifndef _JOINABLE_THREAD_IMPL_H_
#define _JOINABLE_THREAD_IMPL_H_

//internal
#include "cancellation_token.h"

//std
#include <thread>

struct joinable_thread::impl
{
    std::thread t_;
    cancellation_token token_;
};

template <typename Function, typename... Args>
joinable_thread::joinable_thread(Function&& f, Args&&... args)
  : d_(std::make_unique<impl>())
{
}

#endif //_JOINABLE_THREAD_IMPL_H_