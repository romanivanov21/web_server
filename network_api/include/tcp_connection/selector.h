#ifndef _SELECTOR_H_
#define _SELECTOR_H_

#include "event.h"

#include <memory>

namespace network
{
    class selector
    {
    public:
        selector()
        {
        }
        ~selector()
        {
        }

        void add_connection(const slave_connection_unique_ptr& client)
        {
        }
        void is_data_ready()
        {
        }

        event<const std::vector<char>&> data_ready;

    private:
        struct impl;
        std::unique_ptr<impl> d_;
    };
}

#endif //_SELECTOR_H_