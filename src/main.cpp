/**
 *  Файл: main.cpp
 *
 *  Описание: реализация функции main - точка входа в приложение
 */

#include "daemon.h"

#include <memory>
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        daemon_tool::init_config();
        daemon_tool::init_log();
    }
    catch(...)
    {

    }

    std::shared_ptr<daemon_tool> daemon(new daemon_tool);
    try
    {
        daemon->start_daemon();
    }
    catch (...)
    {

    }

    return 0;
}

