/**
 * Файл: server_config.h
 *
 * Описание: класс server_config_exception реализует тип исключений,
 *           которые могут возниктуть при разборе конфигурационного файла
 */

#include <string>
#include <exception>

class server_config_exception : public std::exception
{
 public:
    server_config_exception( const std::string& ex );
    ~server_config_exception( );

    const char* what( ) noexcept;

 private:
    const std::string& ex_;
};
