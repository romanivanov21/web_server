#include "en_user_msg_parser.h"

#include <cassert>

const std::string& en_user_msg_parser::find_user_msg( msg_type msg ) const noexcept
{
    assert( msg < msg_type::msg_end );

    return en_user_msg_[msg];
}

const std::string en_user_msg_parser::en_user_msg_[] =
{
    "System_error",                                           // msg_system_error
    "Error in server config file. Can not parse file",        // msg_config_error
    "Can not found server name in server config file",        // msg_server_name_error
    "Can not found ip address version in server config file", // msg_ip_version_error
    "Ip_version is not valid",                                // msg_not_valid_ip_ver
    "Can not found ip address in server config file",         // msg_ip_address_error
    "Ip address is not valid",                                // msg_not_valid_ip
    "Listen is not valid",                                    // msg_not_valid_listen
    "Can not found listen in server config file",             // msg_listen_error
    "Can not found document root in server config file",      // msg_document_root_error
    "Can not found access log path in server config file",    // msg_access_log_error
    "Can not found error log path in server config file",     // msg_error_log_error
    "Can not found struct 'Server'",                          // msg_server_not_found
    "Can not found struct 'Connection'",                      // msg_connection_not_found
    "Can not found struct 'Directories'",                     // msg_directories_not_found
    "Can not found struct 'Logs'",                            // msg_logs_not_found
    "Can not create error log file",                          // msg_init_error_log_err
    "Can not create access log file",                         // msg_init_access_log_err
    "System error. Can not to start server"                   // msg_start_daemon_err
};