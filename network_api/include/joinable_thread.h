#ifndef _JOINABLE_THREAD_H_
#define _JOINABLE_THREAD_H_

#include <memory>

class joinable_thread
{
public:
    template <typename Function, typename... Args>
    joinable_thread(Function&& f, Args&&... args);

    ~joinable_thread();

    static std::size_t hardware_concurrency() noexcept;

    joinable_thread(const joinable_thread& other) = delete;

    joinable_thread& operator=(const joinable_thread& other) = delete;

public:
    struct impl;
    std::unique_ptr<impl> d_;
};

using joinable_thread_unique_ptr = std::unique_ptr<joinable_thread>;

#endif //_JOINABLE_THREAD_H_

#include "joinable_thread_impl.h"
