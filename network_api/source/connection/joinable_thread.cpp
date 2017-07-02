#include "joinable_thread.h"

joinable_thread::~joinable_thread()
{
    if(d_->t_.joinable())
    {
        d_->token_();
        d_->t_.join();
    }
}

std::size_t joinable_thread::hardware_concurrency() noexcept
{
    return std::thread::hardware_concurrency();
}