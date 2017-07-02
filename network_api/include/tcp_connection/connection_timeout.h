#ifndef _CONNECTION_TIMEOUT_H_
#define _CONNECTION_TIMEOUT_H_

namespace network
{
    struct connection_timeout
    {
        connection_timeout(const std::uint32_t& send_time_s = 0,
                           const std::uint32_t& send_time_us = 0,
                           const std::uint32_t& rcv_time_s = 0,
                           const std::uint32_t& rcv_time_us = 0)
          : send_time_s_(send_time_s), send_time_us_(send_time_us),
            rcv_time_s_(rcv_time_s), rcv_time_us_(rcv_time_us) { }

        std::uint32_t send_time_s_ = 0;  ///!< Таймаут на отправку данных в секундах
        std::uint32_t send_time_us_ = 0; ///!< Таймаут на отправку данных в нано секундах
        std::uint32_t rcv_time_s_ = 0;   ///!< Таймаут на приём данных в секунтах
        std::uint32_t rcv_time_us_ = 0;  ///!< Таймаут на приём данных в наносекундах
    };

} //namespace

#endif //_CONNECTION_TIMEOUT_H_