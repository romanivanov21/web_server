#include "user_msg_parser.h"
#include "en_user_msg_parser.h"

user_msg_parser* user_msg_parser::instance_ = nullptr;
singleton_destroyer<user_msg_parser> user_msg_parser::destroyer_;

user_msg_parser* user_msg_parser::get_instance() noexcept
{
    if( instance_ == nullptr )
    {
#ifdef LANG_EN
            instance_ = new en_user_msg_parser();
#else //default
            instance_ = new en_user_msg_parser();
#endif

    }
    destroyer_.init_obj( instance_ );
    return instance_;
}