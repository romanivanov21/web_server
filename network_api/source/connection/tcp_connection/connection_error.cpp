#include "connection_error.h"

using namespace network;

connection_error::connection_error(error_type err) : err_(err) { }

std::string connection_error::what() const noexcept
{
    std::string res = std::string();
    switch(err_)
    {
    case connection_error::error_type::SOCKET_ERROR:
        res = "Can't create socket";
        break;
    case connection_error::error_type::BIND_ERROR:
        res = "Bind error";
        break;
    case connection_error::error_type::LISTEN_ERROR:
        res = "Listen error";
        break;
    case connection_error::error_type::ACCEPT_ERROR:
        res = "Accept error";
        break;
    case connection_error::error_type::SET_REUSADDR_ERROR:
        res = "Reusaddr error";
        break;
    case connection_error::error_type::SET_NONBLOCK_ERROR:
        res = "Nonblock error";
        break;
    case connection_error::error_type::SET_TIMEOUT_ERROR:
        res = "Timeout set error";
        break;
    case connection_error::error_type::SOCKET_CLOSE_ERROR:
        res = "Connection close error";
        break;
    default:
        res = "Unknown error";
        break;
    }
    return res.c_str();
}

connection_error::error_type connection_error::get_error_type() const noexcept
{ return err_; }
