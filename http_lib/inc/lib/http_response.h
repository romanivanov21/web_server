#ifndef _HTTP_RESPONSE_H_
#define _HTTP_RESPONSE_H_

class http_response
{
public:
    http_response() = default;
    ~http_response() = default;

    http_response( const http_response& copy )  = delete;
    http_response& operator=( const http_response& copy ) = delete;
};

#endif //_HTTP_RESPONSE_H_