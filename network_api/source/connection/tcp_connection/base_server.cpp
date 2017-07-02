#include "base_server.h"

using network::base_server;

void base_server::error_callback(const error_callback_function &callback)
{
    error.connect(callback);
}
