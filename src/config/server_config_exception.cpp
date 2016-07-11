#include "server_config_exception.h"

server_config_exception::server_config_exception( const std::string &ex ) : ex_( ex ) { }

server_config_exception::~server_config_exception( ) { }

const char* server_config_exception::what( ) noexcept { return ex_.c_str(); }