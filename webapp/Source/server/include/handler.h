#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <exception>

#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"

#include <boost/date_time/posix_time/posix_time.hpp>

#include "constants.h"
#include "portfolio.h"
#include "stock.h"
#include "trader.h"
#include "transaction.h"
#include "response.h"

long get_current_timestamp();

typedef std::map<std::string, std::string> parameterlist;
typedef void (*requesthandler)(web::http::http_request, parameterlist);
typedef std::map<std::string, requesthandler> handlermap;
typedef std::map<std::string, handlermap> methodmap;

class Handler {
private:
	static methodmap init_map();

public:
	static methodmap path_map;

	Handler();
	~Handler();

	static void handle_trader(web::http::http_request request, parameterlist params);
	static void handle_quote(web::http::http_request request, parameterlist params);
	static void handle_portfolio(web::http::http_request request, parameterlist params);
	static void handle_transactions(web::http::http_request request, parameterlist params);
	static void handle_portfoliolist(web::http::http_request request, parameterlist params);

	static void handle_register(web::http::http_request request, parameterlist params);
	static void handle_login(web::http::http_request request, parameterlist params);

	static void handle_buy(web::http::http_request request, parameterlist params);
	static void handle_sell(web::http::http_request request, parameterlist params);
};

#endif /* HANDLER_H */
