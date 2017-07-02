#ifndef _SELECTOR_TRAITS_H_
#define _SELECTOR_TRAITS_H_

//std
#include <memory>

namespace network
{
    class base_selector;
    using base_selector_unique_ptr = std::unique_ptr<base_selector>;
    using base_selector_shared_ptr = std::shared_ptr<base_selector>;
    using base_selector_weak_prr = std::weak_ptr<base_selector>;

    enum class selector_error : std::uint32_t
    {
        ADD_ERROR,
        DELETE_ERROR,
        UNKNOWN_ERROR
    };

} //namespace

#endif //_SELECTOR_TRAITS_H_