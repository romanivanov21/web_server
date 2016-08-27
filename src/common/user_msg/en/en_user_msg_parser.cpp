#include "en_user_msg_parser.h"
#include "en_user_msg.h"

#include <cassert>

const std::string& en_user_msg_parser::find_user_msg( msg_type msg ) const noexcept
{
    assert( msg < msg_type::msg_end );

    return en_user_msg[msg];
}