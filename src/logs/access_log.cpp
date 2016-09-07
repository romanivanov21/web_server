#include "access_log.h"

access_log* access_log::log = nullptr;
destroyer_singleton<access_log> access_log::destroyer;

access_log* access_log::get_instance() noexcept
{
    if (!log)
    {
        log = new access_log;
        destroyer.initialize(log);
    }

    return log;
}