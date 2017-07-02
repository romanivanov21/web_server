#ifndef _CANCELLATION_TOKEN_H_
#define _CANCELLATION_TOKEN_H_

#include <atomic>

class cancellation_token
{
public:
    cancellation_token() : cancelled_( false ) { }
    ~cancellation_token() = default;

    void operator()() noexcept { cancelled_ = true; }

private:
    std::atomic<bool> cancelled_;
};

#endif //_CANCELLATION_TOCKEN_H_