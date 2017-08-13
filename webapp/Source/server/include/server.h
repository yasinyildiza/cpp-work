#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>

#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"

#include "constants.h"
#include "trader.h"
#include "handler.h"

class SimpleServer {
public:
    SimpleServer() { }
    SimpleServer(std::string url);

    pplx::task<void> open();
    pplx::task<void> close();

private:
    web::http::experimental::listener::http_listener m_listener;

	bool authenticate(web::http::http_request request, parameterlist params);
    void handle_request(web::http::http_request request, std::string method_name);
    void handle_get(web::http::http_request request);
    void handle_post(web::http::http_request request);
    void handle_put(web::http::http_request request);
    void handle_delete(web::http::http_request request);
};

#endif /* SERVER_H */
