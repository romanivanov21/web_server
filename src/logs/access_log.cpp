#include "access_log.h"

access_log * access_log::log = 0;

access_log::access_log()
{
}

access_log::~access_log()
{
    delete log;
}

access_log * access_log::get_instance() noexcept
{
    if (!log)
        log = new access_log;

    return log;
}

void access_log::set_log_dir(const std::string & dir)
{
    dir_ = dir;
}

void access_log::create_log_file(void) const
{
}

void access_log::open_log_file(void)
{
}

void access_log::write_to_log_file(const std::string & msg) const
{
}

void access_log::close_log_file(void)
{
}