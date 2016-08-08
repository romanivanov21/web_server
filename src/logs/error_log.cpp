#include "error_log.h"

error_log * error_log::log = 0;

error_log::error_log()
{
}

error_log::~error_log()
{
    delete log;
}

error_log * error_log::get_instance() noexcept
{
    if (!log)
        log = new error_log;

    return log;
}

void error_log::set_log_dir(const std::string & dir)
{
    dir_ = dir;
}

void error_log::create_log_file(void) const
{
}

void error_log::open_log_file(void)
{
}

void error_log::write_to_log_file(const std::string & msg) const
{
}

void error_log::close_log_file(void)
{
}
