#include "../include/handler.h"

long get_current_timestamp() {
    return boost::posix_time::microsec_clock::local_time().time_of_day().total_milliseconds() / 1000;
}

methodmap Handler::path_map = Handler::init_map();

Handler::Handler() {}

Handler::~Handler() {}

methodmap Handler::init_map() {
	methodmap m;

    handlermap get_map;
    get_map[URL_TRADER] = Handler::handle_trader;
	get_map[URL_QUOTE] = Handler::handle_quote;
    get_map[URL_PORTFOLIO] = Handler::handle_portfolio;
	get_map[URL_TRANSACTIONS] = Handler::handle_transactions;
	get_map[URL_PORTFOLIOLIST] = Handler::handle_portfoliolist;

    handlermap post_map;
	post_map[URL_REGISTER] = Handler::handle_register;
    post_map[URL_LOGIN] = Handler::handle_login;

    handlermap put_map;
	put_map[URL_SELL] = Handler::handle_sell;
	put_map[URL_BUY] = Handler::handle_buy;

    handlermap del_map;

    m[METHOD_GET] = get_map;
    m[METHOD_POST] = post_map;
    m[METHOD_PUT] = put_map;
    m[METHOD_DEL] = del_map;

	return m;
}

void Handler::handle_trader(web::http::http_request request, parameterlist params) {
    auto username = params.find(KEY_USERNAME);

    Trader trader;
    Trader::find_by_username(username->second, trader);
    request.reply(web::http::status_codes::OK, Response().success(trader.to_json()));
}

void Handler::handle_quote(web::http::http_request request, parameterlist params) {
	auto stockcode = params.find(KEY_STOCKCODE);
    if(stockcode == params.end()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterMissingStockCode));
        return;
    }

    Stock stock;
    Stock::find_by_stockcode(stockcode->second, stock);

    if(stock.exists()) {
        request.reply(web::http::status_codes::OK, Response().success(stock.to_json()));
    } else {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::RecordNotFoundStock));
    }
}

void Handler::handle_portfolio(web::http::http_request request, parameterlist params) {
    auto username = params.find(KEY_USERNAME);
    auto stockcode = params.find(KEY_STOCKCODE);
    if(stockcode == params.end()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterMissingStockCode));
        return;
    }

    Portfolio portfolio;
    Portfolio::find_by_username_and_stockcode(username->second, stockcode->second, portfolio);

    if(portfolio.exists()) {
        request.reply(web::http::status_codes::OK, Response().success(portfolio.to_json()));
    } else {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::RecordNotFoundPortfolio));
    }
}

void Handler::handle_transactions(web::http::http_request request, parameterlist params) {
	auto username = params.find(KEY_USERNAME);
    auto transactions = Transaction::filter_by_username(username->second);

    int counter = 0;
    web::json::value records = web::json::value::array(transactions.size());
    for(auto i=transactions.begin(); i!=transactions.end(); i++) {
        records[counter++] = (*i).to_json();
    }
    web::json::value payload = web::json::value::object();
    payload[KEY_RECORDS] = records;

    request.reply(web::http::status_codes::OK, Response().success(payload));
}

void Handler::handle_portfoliolist(web::http::http_request request, parameterlist params) {
	auto username = params.find(KEY_USERNAME);
    auto portfoliolist = Portfolio::filter_by_username(username->second);

    int counter = 0;
    web::json::value records = web::json::value::array(portfoliolist.size());
    for(auto i=portfoliolist.begin(); i!=portfoliolist.end(); i++) {
        records[counter++] = (*i).to_json();
    }
    web::json::value payload = web::json::value::object();
    payload[KEY_RECORDS] = records;

    request.reply(web::http::status_codes::OK, Response().success(payload));
}

void Handler::handle_register(web::http::http_request request, parameterlist params) {
	auto username = params.find(KEY_USERNAME);
    auto password = params.find(KEY_PASSWORD);

    if(username == params.end()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterMissingUsername));
        return;
    }

    if(password == params.end()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterMissingPassword));
        return;
    }

    Trader trader;
    Trader::find_by_username(username->second, trader);
    if(trader.exists()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::TraderAlreadyRegistered));
    } else {
        Trader::create(username->second, password->second, 100000);
        request.reply(web::http::status_codes::OK, Response().success());
    }
}

void Handler::handle_login(web::http::http_request request, parameterlist params) {
    request.reply(web::http::status_codes::OK, Response().success());
}

void Handler::handle_sell(web::http::http_request request, parameterlist params) {
	auto username = params.find(KEY_USERNAME);
    auto stockcode = params.find(KEY_STOCKCODE);
    auto quantity_param = params.find(KEY_QUANTITY);
    auto price_param = params.find(KEY_PRICE);

    if(stockcode == params.end()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterMissingStockCode));
        return;
    }

    if(quantity_param == params.end()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterMissingQuantity));
        return;
    }

    if(price_param == params.end()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterMissingPrice));
        return;
    }

    int quantity, price;

    try {
        quantity = stoi(quantity_param->second);
    } catch(std::exception& e) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterInvalidQuantity));
        return;
    }

    try {
        price = stoi(price_param->second);
    } catch(std::exception& e) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterInvalidPrice));
        return;
    }

    Stock stock;
    Stock::find_by_stockcode(stockcode->second, stock);
    if(stock.exists()) {
        Portfolio portfolio;
        Portfolio::find_by_username_and_stockcode(username->second, stockcode->second, portfolio);
        if(portfolio.exists()) {
            if(quantity <= portfolio.quantity) {
                Transaction::Status status = Transaction::Status::pending;
                if(stock.lastsaleprice >= price) {
                    portfolio.quantity -= quantity;
                    portfolio.totalcost -= quantity * price;
                    portfolio.update();

                    stock.lastsaleprice = price;
                    stock.update();

                    Trader trader;
                    Trader::find_by_username(username->second, trader);
                    trader.balancecash += quantity * price;
                    trader.update();

                    status = Transaction::Status::executed;
                }
                Transaction::create(username->second, stockcode->second, quantity, get_current_timestamp(), (int)Transaction::Action::sell, (int)status);

                request.reply(web::http::status_codes::OK, Response().success());
            } else {
                request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::NotEnoughPortfolioQuantity));
            }
        } else {
            request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::RecordNotFoundPortfolio));
        }
    } else {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::RecordNotFoundStock));
    }
}

void Handler::handle_buy(web::http::http_request request, parameterlist params) {
	auto username = params.find(KEY_USERNAME);
    auto stockcode = params.find(KEY_STOCKCODE);
    auto quantity_param = params.find(KEY_QUANTITY);
    auto price_param = params.find(KEY_PRICE);

    if(stockcode == params.end()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterMissingStockCode));
        return;
    }

    if(quantity_param == params.end()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterMissingQuantity));
        return;
    }

    if(price_param == params.end()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterMissingPrice));
        return;
    }

    int quantity, price;

    try {
        quantity = stoi(quantity_param->second);
    } catch(std::exception& e) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterInvalidQuantity));
        return;
    }

    try {
        price = stoi(price_param->second);
    } catch(std::exception& e) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterInvalidPrice));
        return;
    }

    Stock stock;
    Stock::find_by_stockcode(stockcode->second, stock);
    if(stock.exists()) {
        Portfolio portfolio;
        Portfolio::find_by_username_and_stockcode(username->second, stockcode->second, portfolio);
        Trader trader;
        Trader::find_by_username(username->second, trader);

        int cost = quantity * price;
        if(cost <= trader.balancecash) {
            Transaction::Status status = Transaction::Status::pending;
            if(stock.lastsaleprice <= price) {
                if(portfolio.exists()) {
                    portfolio.quantity += quantity;
                    portfolio.totalcost += cost;
                    portfolio.update();
                } else {
                    Portfolio::create(username->second, stockcode->second, quantity, cost);
                }

                stock.lastsaleprice = price;
                stock.update();

                trader.balancecash -= cost;
                trader.update();

                status = Transaction::Status::executed;
            }
            Transaction::create(username->second, stockcode->second, quantity, get_current_timestamp(), (int)Transaction::Action::buy, (int)status);

            request.reply(web::http::status_codes::OK, Response().success());
        } else {
            request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::NotEnoughTraderBalanceCash));
        }
    } else {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::RecordNotFoundStock));
    }
}
