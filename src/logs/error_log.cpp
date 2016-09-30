#include "error_log.h"

error_log* error_log::log = nullptr;
destroyer_singleton<error_log> error_log::destroyer;

error_log* error_log::get_instance() noexcept
{
    if (!log)
    {
        log = new error_log;
        destroyer.init_obj(log);
    }

    return log;
}