#include "event_void_spec.h"

#include <map>

struct event<void>::impl
{
    using event_table = std::map<event_id, void_function>;

    event_id current_id_ { 0 };
    event_table table_ { };
};

event<void>::event() : d_(std::make_unique<impl>()) { }

event<void>::~event() = default;

event_id event<void>::connect(void_function const& delegate) const noexcept
{
    d_->table_.insert(std::make_pair(++d_->current_id_, delegate));
    return d_->current_id_;
}

void event<void>::disconnect(event_id event) const noexcept
{
    d_->table_.erase(event);
}

void event<void>::emit() noexcept
{
    for(const auto& it : d_->table_)
    {
        it.second();
    }
}
