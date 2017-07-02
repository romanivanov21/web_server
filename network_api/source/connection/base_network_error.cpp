#include "base_network_error.h"

using namespace network;

base_network_error::base_network_error(network_error_type error)
  : error_(error)
{
}

base_network_error::~base_network_error() = default;

std::string base_network_error::what() const noexcept
{
    std::string str = "";
    switch(error_)
    {
    case base_network_error::network_error_type::memory_allocate_error:
        str = "Memory allocate error";
        break;
    }

    return str;
}