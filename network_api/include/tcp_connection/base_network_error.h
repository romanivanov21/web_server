#ifndef _BASE_NETWORK_ERROR_H_
#define _BASE_NETWORK_ERROR_H_

#include <string>

namespace network
{
    class base_network_error
    {
    public:
        enum class network_error_type
        {
            memory_allocate_error = 0              /* ошибка выделения памяти */
        };

        base_network_error(network_error_type error);

        virtual ~base_network_error();

        virtual std::string what() const noexcept;

    private:
        network_error_type error_;
    };
}

#endif //_BASE_NETWORK_ERROR_H_