#ifndef _EVENT_VOID_SPEC_H_
#define _EVENT_VOID_SPEC_H_

#include "event_traits.h"

#include <functional>
#include <memory>

template <typename... Args>
class event;

template<>
class event<void>
{
public:
    using void_function = std::function<void()>;

    event();

    ~event();

    event_id connect(void_function const&) const noexcept;

    void disconnect(event_id) const noexcept;

    void emit() noexcept;

    event(const event&) = delete;

    event& operator=(event&) = delete;

    event(event&&) = default;

    event& operator=(event&&) = default;

private:
    struct impl;
    std::unique_ptr<impl> d_;
};

#endif //_EVENT_VOID_SPEC_H_