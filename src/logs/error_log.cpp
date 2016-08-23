#include "error_log.h"

#include <cassert>
#include <fstream>
#include <iostream>

error_log* error_log::log = nullptr;
destroyer_singleton<error_log> error_log::destroyer;

error_log* error_log::get_instance() noexcept
{
    if (!log)
    {
        log = new error_log;
        destroyer.initialize(log);
    }

    return log;
}

void error_log::init_log_file(const std::string& file_name)
{
    assert(!file_name.empty());
    log_filename_ = file_name;

    try
    {
        save_log("logfile error initialization complete");
    }
    catch(...)
    {
        throw;
    }
}

void error_log::save_log(const std::string& msg)
{
    assert(!msg.empty());

    std::string log_msg;
    try
    {
        log_msg = create_log_struct(msg);
    }
    catch(...)
    {
        throw;
    }

    std::ofstream stream;
    stream.open(log_filename_, std::ios::out | std::ios::app);
    if (!stream)
    {
        throw;
    }

    stream.write(log_msg.c_str(), log_msg.size());
    stream.close();
}