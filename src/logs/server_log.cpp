#include "server_log.h"

#include <cassert>

const std::string server_log::create_log_struct(const std::string & msg) noexcept
{
    assert( !msg.empty() );

    std::string new_msg = get_data_time() + msg + "\n";

    return new_msg;
}

const std::string server_log::get_data_time(void) noexcept
{
    char buffer[80];
    time_t raw_time;
    struct tm * time_info;

    time (&raw_time);
    time_info = localtime(&raw_time);

    strftime(buffer, 80, "[ %d-%m-%Y %I:%M:%S ] ", time_info);

    return static_cast<std::string>(buffer);
}