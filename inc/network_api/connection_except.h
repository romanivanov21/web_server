#ifndef _CONNECTION_EXCEPT_H_
#define _CONNECTION_EXCEPT_H_

#include <stdexcept>

class connection_except : public std::exception
{
public:
    enum class error_type
    {
        SOCKET_ERROR = 0,      //!< ошибка системного вызова socket()
        BIND_ERROR,            //!< ошибка системного вызова bind()
        LISTEN_ERROR,          //!< ошибка системного вызова listen()
        ACCEPT_ERROR,          //!< ошибка системного вызова accept()
        SET_NONBLOCK_ERROR,    //!< ошибка перевод сокет в неблокирующий режиим
        SET_REUSADDR_ERROR,    //!< ошибка установки опции reusaddr
        SET_TIMEOUT_ERROR      //!< ошибка установки таймаута
    };
public:
    explicit connection_except( error_type err );

    ~connection_except() = default;

    const char* what() const noexcept;

    connection_except::error_type get_error_type() const noexcept;

private:
    error_type err_;
};

#endif //_CONNECTION_EXCEPT_H_