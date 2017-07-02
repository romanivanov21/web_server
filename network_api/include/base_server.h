#ifndef _BASE_SERVER_H_
#define _BASE_SERVER_H_

//internal
#include "event_traits.h"
#include "base_network_error.h"
#include "event.h"

//stl
#include <functional>

namespace network
{
    class base_server
    {
    public:
        using error_callback_function =
          std::function<void(const base_network_error&)>;

        virtual ~base_server() = default;

        virtual void run() noexcept = 0;

        void error_callback
          (error_callback_function const& callback);

    protected:
        event<const base_network_error&> error;
    };

} //namespace

#endif //_BASE_SERVER_H_
