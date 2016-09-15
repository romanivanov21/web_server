#include "msg_type.h"
#include "daemon_tool_exception.h"

daemon_tool_exception::daemon_tool_exception( msg_type msg ) noexcept :
  msg_( user_msg_parser::get_instance()->find_user_msg( msg ) ) { }

const char* daemon_tool_exception::what() const noexcept { return msg_.c_str(); }