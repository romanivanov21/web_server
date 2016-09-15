#include "user_msg_parser.h"
#include "serevr_log_exception.h"

server_log_exception::server_log_exception( msg_type msg ) noexcept :
  msg_( user_msg_parser::get_instance()->find_user_msg( msg ) ) { }

const char* server_log_exception::what() const noexcept { return msg_.c_str(); }
