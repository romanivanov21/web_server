#ifndef _UNIT_TESTS_H_
#define _UNIT_TESTS_H_

#include "http_request_parser.h"
#include "http_request.h"

#include <string>
#include <gtest/gtest.h>

TEST( request001, httpparsertest )
{
    const std::string request = "GET /web_server.ru HTTP/1.1\r\n"
      "User-Agent: Mozilla/5.0\r\n"
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
      "Host: web_server.ru\r\n"
      "\r\n";
    http_request parse_request;
    http_request_parser parser;
    parser.parse( request, parse_request );

    ASSERT_EQ( parse_request.method_, "GET" );
    ASSERT_EQ( parse_request.headers_["User-Agent"], "Mozilla/5.0" );
    ASSERT_EQ( parse_request.headers_["Accept"], "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8" );
    ASSERT_EQ( parse_request.headers_["Host"], "web_server.ru" );
}

#endif //_UNIT_TEST_H_