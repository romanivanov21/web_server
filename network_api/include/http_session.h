#ifndef _HTTP_SESSION_H_
#define _HTTP_SESSION_H_

#include "base_user_session.h"

namespace network
{
    class http_session : public base_user_session
    {
    public:
        void init(const slave_connection_unique_ptr& connection) override;

        void on_error() noexcept override;

        void on_timeout() noexcept override;

        void done() noexcept override;

        void on_receive_data
          (const byte_vector& buffer) noexcept override;

        void on_idle() noexcept override;
    };
}

#endif _HTTP_SESSION_H_