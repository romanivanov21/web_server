#ifndef _HTTP_REQUEST_H_
#define _HTTP_REQUEST_H_

#include <unordered_map>
#include <string>

struct http_request
{
    http_request()
      : method_( "" ), uri_( "" ), version_major_( 0 ), version_minor_( 0 ), headers_( 0 ),
        content_( "" ), is_alive_( false ) { }

    /* HTTP метод */
    std::string method_;
    /* URI */
    std::string uri_;
    int version_major_;
    int version_minor_;
    std::unordered_map<std::string, std::string> headers_;
    std::string content_;
    bool is_alive_;
};

#endif //_HTTP_REQUEST_H_