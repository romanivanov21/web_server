#ifndef _HTTP_REQUEST_H_
#define _HTTP_REQUEST_H_

class http_request
{
public:
    http_request() = default;
    ~http_request() = default;

    http_request( const http_request& copy ) = delete;
    http_request& operator=( const http_request& copy ) = delete;
};

#endif //_HTTP_REQIEST_H_