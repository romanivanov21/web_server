#ifndef _USER_SESSION_TRAITS_H_
#define _USER_SESSION_TRAITS_H_

#include <memory>

namespace network
{
    class base_user_session;
    using base_user_session_ptr = std::unique_ptr<base_user_session>;
}

#endif //_USER_SESSION_TRAITS_H_