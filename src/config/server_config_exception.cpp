#include "server_config_exception.h"

server_config_exception::server_config_exception( const std::string &ex ) noexcept : ex_( ex ) { }

server_config_exception::~server_config_exception( ) noexcept { }

const char* server_config_exception::what() const noexcept { return ex_.c_str(); }