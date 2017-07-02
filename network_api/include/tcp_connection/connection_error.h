#ifndef _CONNECTION_ERROR_H_
#define _CONNECTION_ERROR_H_

//std
#include <string>

namespace network
{
    class connection_error
    {
    public:
        enum class error_type : std::uint32_t
        {
            SOCKET_ERROR = 0,      //!< ошибка системного вызова socket()
            BIND_ERROR,            //!< ошибка системного вызова bind()
            LISTEN_ERROR,          //!< ошибка системного вызова listen()
            ACCEPT_ERROR,          //!< ошибка системного вызова accept()
            SET_NONBLOCK_ERROR,    //!< ошибка перевод сокет в неблокирующий режиим
            SET_REUSADDR_ERROR,    //!< ошибка установки опции reusaddr
            SET_TIMEOUT_ERROR,     //!< ошибка установки таймаута
            SOCKET_CLOSE_ERROR     //!< ошибка закрытия сокета
        };
    public:
        explicit connection_error(error_type err);

        ~connection_error() = default;

        std::string what() const noexcept;

        connection_error::error_type get_error_type() const noexcept;

    private:
        connection_error::error_type err_;
    };
}

#endif //_CONNECTION_EXCEPT_H_