#ifndef _BASE_USER_SESSION_H_
#define _BASE_USER_SESSION_H_

#include "byte_vector.h"
#include "connection_traits.h"

namespace network
{
    class base_user_session
    {
    public:
        virtual ~base_user_session() = default;

        virtual void init(const slave_connection_unique_ptr& connection) noexcept = 0;

        virtual void on_error() noexcept = 0;

        virtual void on_timeout() noexcept = 0;

        virtual void done() noexcept = 0;

        virtual void on_receive_data
          (const byte_vector& buffer) noexcept = 0;

        virtual void on_idle() noexcept = 0;
    };

} //nmaespace

#endif //_BASE_USER_SESSION_H_