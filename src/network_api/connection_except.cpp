#include "connection_except.h"

connection_except::connection_except( error_type err ) : err_( err ) { }

const char* connection_except::what() const noexcept
{
    std::string res = "";
    switch( err_ )
    {
        case connection_except::error_type::SOCKET_ERROR:
            res = "Can't create socket";
            break;
        case connection_except::error_type::BIND_ERROR:
            res = "Bind error";
            break;
        case connection_except::error_type::LISTEN_ERROR:
            res = "Listen error";
            break;
        case connection_except::error_type::ACCEPT_ERROR:
            res = "Accept error";
            break;
        case connection_except::error_type::SET_REUSADDR_ERROR:
            res = "Reusaddr error";
            break;
        case connection_except::error_type::SET_NONBLOCK_ERROR:
            res = "Nonblock error";
            break;
        case connection_except::error_type::SET_TIMEOUT_ERROR:
            res = "Timeout set error";
            break;
        default:
            res = "Unknown error";
            break;
    }
    return res.c_str();
}

connection_except::error_type connection_except::get_error_type() const noexcept { return err_; }
