#ifndef _MSG_TYPE_H_
#define _MSG_TYPE_H_

enum msg_type
{
    msg_system_error = 0,
    msg_config_error,
    msg_server_name_error,
    msg_ip_version_error,
    msg_not_valid_ip_ver,
    msg_ip_address_error,
    msg_not_valid_ip,
    msg_not_valid_listen,
    msg_listen_error,
    msg_document_root_error,
    msg_access_log_error,
    msg_error_log_error,
    msg_server_not_found,
    msg_connection_not_found,
    msg_directories_not_found,
    msg_logs_not_found,

    msg_end //последний элемент перечисления
};
#endif //_MSG_H_