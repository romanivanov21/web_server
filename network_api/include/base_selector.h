#ifndef _BASE_SELECTOR_H_
#define _BASE_SELECTOR_H_

//internal
#include "connection_traits.h"
#include "selector_traits.h"
#include "event.h"

//std
#include <functional>

namespace network
{
    class base_selector
    {
    public:
        using data_ready_function =
        std::function<void(const network::slave_connection_shared_ptr&)>;

        using error_function =
        std::function<void(const network::selector_error&)>;

        virtual ~base_selector() = default;

        virtual void add_connection
          (const network::slave_connection_shared_ptr&) noexcept = 0;

        virtual void delete_connection
          (const network::slave_connection_shared_ptr&) noexcept = 0;

        virtual void check_data_ready
          (int max_event, int wait_timeout) noexcept = 0;

        void data_ready_callback
          (data_ready_function const& f) noexcept;

        void error_callback
          (error_function const& f) noexcept;
    protected:
        event<const network::slave_connection_shared_ptr&>
          data_ready;

        event<const network::selector_error&> error;
    };

} // namespace

#endif //_BASE_SELECTOR_H_