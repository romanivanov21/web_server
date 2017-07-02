#include "base_selector.h"

using network::base_selector;

base_selector::~base_selector() = default;

void base_selector::data_ready_callback
  (data_ready_function const& f) noexcept
{
    data_ready.connect(f);
}

void base_selector::error_callback(error_function const& f) noexcept
{
    error.connect(f);
}