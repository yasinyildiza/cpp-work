#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include <string>
#include <exception>
#include <cassert>

#include <cpprest/http_client.h>
#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include <cpprest/http_msg.h>

typedef void (*testcase)(web::uri_builder builder);

const std::string URL_TRADER = "/trader";
const std::string URL_QUOTE = "/quote";
const std::string URL_PORTFOLIO = "/portfolio";
const std::string URL_TRANSACTIONS = "/transactions";
const std::string URL_PORTFOLIOLIST = "/portfoliolist";
const std::string URL_REGISTER = "/register";
const std::string URL_LOGIN = "/login";
const std::string URL_SELL = "/sell";
const std::string URL_BUY = "/buy";

const std::string TEST_USERNAME = "testuser";
const std::string TEST_PASSWORD = "testpass";
const std::string TEST_STOCKCODE1 = "TEST1";
const std::string TEST_STOCKCODE2 = "TEST2";
const std::string TEST_STOCKCODE3 = "TEST3";

const std::string KEY_SUCCESS = "success";
const std::string KEY_PAYLOAD = "payload";
const std::string KEY_ERROR = "error";
const std::string KEY_CODE = "code";
const std::string KEY_MESSAGE = "message";
const std::string KEY_RECORDS = "records";

const std::string KEY_USERNAME = "username";
const std::string KEY_PASSWORD = "password";
const std::string KEY_BALANCECASH = "balancecash";
const std::string KEY_DATETIME = "datetime";
const std::string KEY_ACTION = "action";
const std::string KEY_STATUS = "status";
const std::string KEY_STOCKCODE = "stockcode";
const std::string KEY_LASTSALEPRICE = "lastsaleprice";
const std::string KEY_QUANTITY = "quantity";
const std::string KEY_PRICE = "price";
const std::string KEY_TOTALCOST = "totalcost";

const int ACTION_SELL = 0;
const int ACTION_BUY = 1;

const int STATUS_PENDING = 0;
const int STATUS_EXECUTED = 1;

web::json::value get_response(const web::uri &uri, const web::http::method method) {
    web::http::client::http_client client(uri);
    web::http::http_response response = client.request(method).get();
    web::json::value json = response.extract_json().get();
    return json;
}

web::json::value get_response(web::uri_builder builder, const web::http::method method) {
    return get_response(builder.to_uri(), method);
}

web::json::value get_response_after_authentication(web::uri_builder builder, const web::http::method method) {
    return get_response(builder.append_query(KEY_USERNAME, TEST_USERNAME).append_query(KEY_PASSWORD, TEST_PASSWORD), method);
}

void check_error(web::json::value &json, int error_code, std::string error_message) {
    assert(json.size() == 2);

    auto success = json[KEY_SUCCESS];
    auto payload = json[KEY_PAYLOAD];
    auto error = json[KEY_ERROR];

    auto code = error.as_object()[KEY_CODE];
    auto message = error.as_object()[KEY_MESSAGE];

    assert(success.as_bool() == false);
    assert(payload.is_null() == true);
    assert(error.as_object().size() == 2);
    assert(code.as_integer() == error_code);
    assert(message.as_string() == error_message);
}

web::json::object check_success(web::json::value &json) {
    assert(json.size() == 2);

    auto success = json[KEY_SUCCESS];
    auto payload = json[KEY_PAYLOAD];
    auto error = json[KEY_ERROR];

    assert(success.as_bool() == true);
    assert(payload.is_object() == true);
    assert(error.is_null() == true);

    return payload.as_object();
}

void check_path_missing(web::uri_builder builder, const web::http::method method) {
    auto json = get_response(builder.to_uri(), method);
    check_error(json, 1, "Path Missing");
}

void check_path_not_found(web::uri_builder builder, const web::http::method method) {
    auto json = get_response(builder.append_path("path_not_found").to_uri(), method);
    check_error(json, 2, "Path Not Found");
}

void check_parameter_missing_username(web::uri_builder builder, const web::http::method method) {
    auto json = get_response(builder.append_query(KEY_PASSWORD, TEST_PASSWORD).to_uri(), method);
    check_error(json, 5, "Parameter Missing: Username");
}

void check_parameter_missing_password(web::uri_builder builder, const web::http::method method) {
    auto json = get_response(builder.append_query(KEY_USERNAME, TEST_USERNAME).to_uri(), method);
    check_error(json, 6, "Parameter Missing: Password");
}

void check_authentication_failed(web::uri_builder builder, const web::http::method method) {
    auto json = get_response(builder.append_query(KEY_USERNAME, "nottestuser").append_query(KEY_PASSWORD, "nottestpass").to_uri(), method);
    check_error(json, 3, "Authentication Failed");
}

void test_path_missing_get(web::uri_builder builder) {
    check_path_missing(builder, web::http::methods::GET);
}

void test_path_missing_post(web::uri_builder builder) {
    check_path_missing(builder, web::http::methods::POST);
}

void test_path_missing_put(web::uri_builder builder) {
    check_path_missing(builder, web::http::methods::PUT);
}

void test_path_missing_del(web::uri_builder builder) {
    check_path_missing(builder, web::http::methods::DEL);
}

void test_path_not_found_get(web::uri_builder builder) {
    check_path_not_found(builder, web::http::methods::GET);
}

void test_path_not_found_post(web::uri_builder builder) {
    check_path_not_found(builder, web::http::methods::POST);
}

void test_path_not_found_put(web::uri_builder builder) {
    check_path_not_found(builder, web::http::methods::PUT);
}

void test_path_not_found_del(web::uri_builder builder) {
    check_path_not_found(builder, web::http::methods::DEL);
}

void test_parameter_missing_username_trader(web::uri_builder builder) {
    check_parameter_missing_username(builder.append_path(URL_TRADER), web::http::methods::GET);
}

void test_parameter_missing_password_trader(web::uri_builder builder) {
    check_parameter_missing_password(builder.append_path(URL_TRADER), web::http::methods::GET);
}

void test_authentication_failed_trader(web::uri_builder builder) {
    check_authentication_failed(builder.append_path(URL_TRADER), web::http::methods::GET);
}

void test_parameter_missing_username_quote(web::uri_builder builder) {
    check_parameter_missing_username(builder.append_path(URL_QUOTE), web::http::methods::GET);
}

void test_parameter_missing_password_quote(web::uri_builder builder) {
    check_parameter_missing_password(builder.append_path(URL_QUOTE), web::http::methods::GET);
}

void test_authentication_failed_quote(web::uri_builder builder) {
    check_authentication_failed(builder.append_path(URL_QUOTE), web::http::methods::GET);
}

void test_parameter_missing_username_portfolio(web::uri_builder builder) {
    check_parameter_missing_username(builder.append_path(URL_PORTFOLIO), web::http::methods::GET);
}

void test_parameter_missing_password_portfolio(web::uri_builder builder) {
    check_parameter_missing_password(builder.append_path(URL_PORTFOLIO), web::http::methods::GET);
}

void test_authentication_failed_portfolio(web::uri_builder builder) {
    check_authentication_failed(builder.append_path(URL_PORTFOLIO), web::http::methods::GET);
}

void test_parameter_missing_username_transactions(web::uri_builder builder) {
    check_parameter_missing_username(builder.append_path(URL_TRANSACTIONS), web::http::methods::GET);
}

void test_parameter_missing_password_transactions(web::uri_builder builder) {
    check_parameter_missing_password(builder.append_path(URL_TRANSACTIONS), web::http::methods::GET);
}

void test_authentication_failed_transactions(web::uri_builder builder) {
    check_authentication_failed(builder.append_path(URL_TRANSACTIONS), web::http::methods::GET);
}

void test_parameter_missing_username_portfoliolist(web::uri_builder builder) {
    check_parameter_missing_username(builder.append_path(URL_PORTFOLIOLIST), web::http::methods::GET);
}

void test_parameter_missing_password_portfoliolist(web::uri_builder builder) {
    check_parameter_missing_password(builder.append_path(URL_PORTFOLIOLIST), web::http::methods::GET);
}

void test_authentication_failed_portfoliolist(web::uri_builder builder) {
    check_authentication_failed(builder.append_path(URL_PORTFOLIOLIST), web::http::methods::GET);
}

void test_parameter_missing_username_register(web::uri_builder builder) {
    check_parameter_missing_username(builder.append_path(URL_REGISTER), web::http::methods::POST);
}

void test_parameter_missing_password_register(web::uri_builder builder) {
    check_parameter_missing_password(builder.append_path(URL_REGISTER), web::http::methods::POST);
}

void test_parameter_missing_username_login(web::uri_builder builder) {
    check_parameter_missing_username(builder.append_path(URL_LOGIN), web::http::methods::POST);
}

void test_parameter_missing_password_login(web::uri_builder builder) {
    check_parameter_missing_password(builder.append_path(URL_LOGIN), web::http::methods::POST);
}

void test_authentication_failed_login(web::uri_builder builder) {
    check_authentication_failed(builder.append_path(URL_LOGIN), web::http::methods::POST);
}

void test_parameter_missing_username_sell(web::uri_builder builder) {
    check_parameter_missing_username(builder.append_path(URL_SELL), web::http::methods::PUT);
}

void test_parameter_missing_password_sell(web::uri_builder builder) {
    check_parameter_missing_password(builder.append_path(URL_SELL), web::http::methods::PUT);
}

void test_authentication_failed_sell(web::uri_builder builder) {
    check_authentication_failed(builder.append_path(URL_SELL), web::http::methods::PUT);
}

void test_parameter_missing_username_buy(web::uri_builder builder) {
    check_parameter_missing_username(builder.append_path(URL_BUY), web::http::methods::PUT);
}

void test_parameter_missing_password_buy(web::uri_builder builder) {
    check_parameter_missing_password(builder.append_path(URL_BUY), web::http::methods::PUT);
}

void test_authentication_failed_buy(web::uri_builder builder) {
    check_authentication_failed(builder.append_path(URL_BUY), web::http::methods::PUT);
}

void test_parameter_missing_stockcode_quote(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_QUOTE), web::http::methods::GET);
    check_error(json, 7, "Parameter Missing: StockCode");
}

void test_record_not_found_stock_quote(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_QUOTE).append_query(KEY_STOCKCODE, "record_not_found"), web::http::methods::GET);
    check_error(json, 18, "Record Not Found: Stock");
}

void test_parameter_missing_stockcode_portfolio(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_PORTFOLIO), web::http::methods::GET);
    check_error(json, 7, "Parameter Missing: StockCode");
}

void test_record_not_found_portfolio_portfolio(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_PORTFOLIO).append_query(KEY_STOCKCODE, TEST_STOCKCODE3), web::http::methods::GET);
    check_error(json, 17, "Record Not Found: Portfolio");
}

void test_trader_already_registered_register(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_REGISTER).append_query(KEY_USERNAME, TEST_USERNAME).append_query(KEY_PASSWORD, TEST_PASSWORD), web::http::methods::POST);
    check_error(json, 4, "Trader Already Registered");
}

void test_parameter_missing_stockcode_sell(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_SELL).append_query(KEY_QUANTITY, "1").append_query(KEY_PRICE, "2"), web::http::methods::PUT);
    check_error(json, 7, "Parameter Missing: StockCode");
}

void test_parameter_missing_quantity_sell(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_SELL).append_query(KEY_STOCKCODE, TEST_STOCKCODE1).append_query(KEY_PRICE, "2"), web::http::methods::PUT);
    check_error(json, 8, "Parameter Missing: Quantity");
}

void test_parameter_missing_price_sell(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_SELL).append_query(KEY_STOCKCODE, TEST_STOCKCODE1).append_query(KEY_QUANTITY, "1"), web::http::methods::PUT);
    check_error(json, 9, "Parameter Missing: Price");
}

void test_parameter_invalid_quantity_sell(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_SELL).append_query(KEY_STOCKCODE, TEST_STOCKCODE1).append_query(KEY_QUANTITY, "x").append_query(KEY_PRICE, "2"), web::http::methods::PUT);
    check_error(json, 13, "Parameter Invalid: Quantity");
}

void test_parameter_invalid_price_sell(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_SELL).append_query(KEY_STOCKCODE, TEST_STOCKCODE1).append_query(KEY_QUANTITY, "1").append_query(KEY_PRICE, "x"), web::http::methods::PUT);
    check_error(json, 14, "Parameter Invalid: Price");
}

void test_parameter_missing_stockcode_buy(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_BUY).append_query(KEY_QUANTITY, "1").append_query(KEY_PRICE, "2"), web::http::methods::PUT);
    check_error(json, 7, "Parameter Missing: StockCode");
}

void test_parameter_missing_quantity_buy(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_BUY).append_query(KEY_STOCKCODE, TEST_STOCKCODE1).append_query(KEY_PRICE, "2"), web::http::methods::PUT);
    check_error(json, 8, "Parameter Missing: Quantity");
}

void test_parameter_missing_price_buy(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_BUY).append_query(KEY_STOCKCODE, TEST_STOCKCODE1).append_query(KEY_QUANTITY, "1"), web::http::methods::PUT);
    check_error(json, 9, "Parameter Missing: Price");
}

void test_parameter_invalid_quantity_buy(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_BUY).append_query(KEY_STOCKCODE, TEST_STOCKCODE1).append_query(KEY_QUANTITY, "x").append_query(KEY_PRICE, "2"), web::http::methods::PUT);
    check_error(json, 13, "Parameter Invalid: Quantity");
}

void test_parameter_invalid_price_buy(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_BUY).append_query(KEY_STOCKCODE, TEST_STOCKCODE1).append_query(KEY_QUANTITY, "1").append_query(KEY_PRICE, "x"), web::http::methods::PUT);
    check_error(json, 14, "Parameter Invalid: Price");
}

void test_record_not_found_stock_sell(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_SELL).append_query(KEY_STOCKCODE, "NOT_FOUND").append_query(KEY_QUANTITY, "1").append_query(KEY_PRICE, "2"), web::http::methods::PUT);
    check_error(json, 18, "Record Not Found: Stock");
}

void test_record_not_found_portfolio_sell(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_SELL).append_query(KEY_STOCKCODE, TEST_STOCKCODE3).append_query(KEY_QUANTITY, "1").append_query(KEY_PRICE, "2"), web::http::methods::PUT);
    check_error(json, 17, "Record Not Found: Portfolio");
}

void test_not_enough_portfolio_quantity_sell(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_SELL).append_query(KEY_STOCKCODE, TEST_STOCKCODE1).append_query(KEY_QUANTITY, "100").append_query(KEY_PRICE, "2"), web::http::methods::PUT);
    check_error(json, 19, "Not Enough Portfolio Quantity");
}

void test_record_not_found_stock_buy(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_BUY).append_query(KEY_STOCKCODE, "NOT_FOUND").append_query(KEY_QUANTITY, "1").append_query(KEY_PRICE, "2"), web::http::methods::PUT);
    check_error(json, 18, "Record Not Found: Stock");
}

void test_not_enough_trader_balancecash_buy(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_BUY).append_query(KEY_STOCKCODE, TEST_STOCKCODE1).append_query(KEY_QUANTITY, "1000000").append_query(KEY_PRICE, "2"), web::http::methods::PUT);
    check_error(json, 20, "Not Enough Trader BalanceCash");
}

void test_trader(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_TRADER), web::http::methods::GET);
    auto payload = check_success(json);
    assert(payload.size() == 2);
    auto username = payload[KEY_USERNAME];
    auto balancecash = payload[KEY_BALANCECASH];
    assert(username.as_string() == TEST_USERNAME);
    assert(balancecash.is_number() == true);
}

void test_quote1(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_QUOTE).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    auto payload = check_success(json);
    assert(payload.size() == 2);
    auto stockcode = payload[KEY_STOCKCODE];
    auto lastsaleprice = payload[KEY_LASTSALEPRICE];
    assert(stockcode.as_string() == TEST_STOCKCODE1);
    assert(lastsaleprice.is_number() == true);
}

void test_quote2(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_QUOTE).append_query(KEY_STOCKCODE, TEST_STOCKCODE2), web::http::methods::GET);
    auto payload = check_success(json);
    assert(payload.size() == 2);
    auto stockcode = payload[KEY_STOCKCODE];
    auto lastsaleprice = payload[KEY_LASTSALEPRICE];
    assert(stockcode.as_string() == TEST_STOCKCODE2);
    assert(lastsaleprice.is_number() == true);
}

void test_quote3(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_QUOTE).append_query(KEY_STOCKCODE, TEST_STOCKCODE3), web::http::methods::GET);
    auto payload = check_success(json);
    assert(payload.size() == 2);
    auto stockcode = payload[KEY_STOCKCODE];
    auto lastsaleprice = payload[KEY_LASTSALEPRICE];
    assert(stockcode.as_string() == TEST_STOCKCODE3);
    assert(lastsaleprice.is_number() == true);
}

void test_portfolio1(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_PORTFOLIO).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    auto payload = check_success(json);
    assert(payload.size() == 4);
    auto username = payload[KEY_USERNAME];
    auto stockcode = payload[KEY_STOCKCODE];
    auto quantity = payload[KEY_QUANTITY];
    auto totalcost = payload[KEY_TOTALCOST];
    assert(username.as_string() == TEST_USERNAME);
    assert(stockcode.as_string() == TEST_STOCKCODE1);
    assert(quantity.is_number() == true);
    assert(totalcost.is_number() == true);
}

void test_portfolio2(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_PORTFOLIO).append_query(KEY_STOCKCODE, TEST_STOCKCODE2), web::http::methods::GET);
    auto payload = check_success(json);
    assert(payload.size() == 4);
    auto username = payload[KEY_USERNAME];
    auto stockcode = payload[KEY_STOCKCODE];
    auto quantity = payload[KEY_QUANTITY];
    auto totalcost = payload[KEY_TOTALCOST];
    assert(username.as_string() == TEST_USERNAME);
    assert(stockcode.as_string() == TEST_STOCKCODE2);
    assert(quantity.is_number() == true);
    assert(totalcost.is_number() == true);
}

void test_transactions(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_TRANSACTIONS), web::http::methods::GET);
    auto payload = check_success(json);
    assert(payload.size() == 1);
    assert(payload[KEY_RECORDS].is_array() == true);
}

void test_portfoliolist(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_PORTFOLIOLIST), web::http::methods::GET);
    auto payload = check_success(json);
    assert(payload.size() == 1);
    assert(payload[KEY_RECORDS].is_array() == true);
}

void test_register(web::uri_builder builder) {
    web::uri_builder b = builder;
    web::uri_builder b1 = builder;
    web::uri_builder b2 = builder;

    int random;
    web::json::value json;
    std::string username;

    while(true) {
        srand(time(NULL));
        random = rand();

        username = TEST_USERNAME;
        username.append(std::to_string(random));

        b = builder;
        json = get_response(b.append_path(URL_LOGIN).append_query(KEY_USERNAME, username).append_query(KEY_PASSWORD, TEST_PASSWORD), web::http::methods::POST);
        if(json[KEY_SUCCESS].as_bool() == false) {
            break;
        }
    }

    json = get_response(b1.append_path(URL_REGISTER).append_query(KEY_USERNAME, username).append_query(KEY_PASSWORD, TEST_PASSWORD), web::http::methods::POST);
    auto payload = check_success(json);
    assert(payload.size() == 0);

    json = get_response(b2.append_path(URL_LOGIN).append_query(KEY_USERNAME, username).append_query(KEY_PASSWORD, TEST_PASSWORD), web::http::methods::POST);
    payload = check_success(json);
    assert(payload.size() == 0);
}

void test_login(web::uri_builder builder) {
    auto json = get_response_after_authentication(builder.append_path(URL_LOGIN), web::http::methods::POST);
    auto payload = check_success(json);
    assert(payload.size() == 0);
}

void test_sell_pending(web::uri_builder builder) {
    web::uri_builder b1 = builder;
    web::uri_builder b2 = builder;
    web::uri_builder b3 = builder;
    web::uri_builder b4 = builder;
    web::uri_builder b5 = builder;
    web::uri_builder b6 = builder;
    web::uri_builder b7 = builder;
    web::uri_builder b8 = builder;

    auto json = get_response_after_authentication(b1.append_path(URL_QUOTE).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    auto payload = check_success(json);
    auto lastsaleprice = payload[KEY_LASTSALEPRICE].as_integer();

    json = get_response_after_authentication(b2.append_path(URL_TRADER), web::http::methods::GET);
    payload = check_success(json);
    auto balancecash = payload[KEY_BALANCECASH].as_integer();

    json = get_response_after_authentication(b3.append_path(URL_PORTFOLIO).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    payload = check_success(json);
    auto quantity = payload[KEY_QUANTITY].as_integer();
    auto totalcost = payload[KEY_TOTALCOST].as_integer();

    int q = 1;
    int price = lastsaleprice + 1;

    json = get_response_after_authentication(b4.append_path(URL_SELL).append_query(KEY_STOCKCODE, TEST_STOCKCODE1).append_query(KEY_QUANTITY, std::to_string(q)).append_query(KEY_PRICE, std::to_string(price)), web::http::methods::PUT);
    payload = check_success(json);
    assert(payload.size() == 0);

    json = get_response_after_authentication(b5.append_path(URL_QUOTE).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    payload = check_success(json);
    auto lastsaleprice_later = payload[KEY_LASTSALEPRICE].as_integer();

    json = get_response_after_authentication(b6.append_path(URL_TRADER), web::http::methods::GET);
    payload = check_success(json);
    auto balancecash_later = payload[KEY_BALANCECASH].as_integer();

    json = get_response_after_authentication(b7.append_path(URL_PORTFOLIO).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    payload = check_success(json);
    auto quantity_after = payload[KEY_QUANTITY].as_integer();
    auto totalcost_after = payload[KEY_TOTALCOST].as_integer();

    json = get_response_after_authentication(b8.append_path(URL_TRANSACTIONS), web::http::methods::GET);
    web::json::array records = json[KEY_PAYLOAD][KEY_RECORDS].as_array();

    bool found = false;
    for(auto i=records.begin(); i!=records.end(); i++) {
        auto record = i->as_object();
        auto action = record[KEY_ACTION].as_integer();
        auto status = record[KEY_STATUS].as_integer();
        if(action == ACTION_SELL && status == STATUS_PENDING) {
            found = true;
            break;
        }
    }
    
    assert(found == true);
    assert(lastsaleprice == lastsaleprice_later);
    assert(balancecash == balancecash_later);

    assert(quantity == quantity_after);
    assert(totalcost == totalcost_after);
}

void test_sell_executed(web::uri_builder builder) {
    web::uri_builder b1 = builder;
    web::uri_builder b2 = builder;
    web::uri_builder b3 = builder;
    web::uri_builder b4 = builder;
    web::uri_builder b5 = builder;
    web::uri_builder b6 = builder;
    web::uri_builder b7 = builder;
    web::uri_builder b8 = builder;

    auto json = get_response_after_authentication(b1.append_path(URL_QUOTE).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    auto payload = check_success(json);
    auto lastsaleprice = payload[KEY_LASTSALEPRICE].as_integer();

    json = get_response_after_authentication(b2.append_path(URL_TRADER), web::http::methods::GET);
    payload = check_success(json);
    auto balancecash = payload[KEY_BALANCECASH].as_integer();

    json = get_response_after_authentication(b3.append_path(URL_PORTFOLIO).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    payload = check_success(json);
    auto quantity = payload[KEY_QUANTITY].as_integer();
    auto totalcost = payload[KEY_TOTALCOST].as_integer();

    int q = 1;
    int price = lastsaleprice - 1;

    json = get_response_after_authentication(b4.append_path(URL_SELL).append_query(KEY_STOCKCODE, TEST_STOCKCODE1).append_query(KEY_QUANTITY, std::to_string(q)).append_query(KEY_PRICE, std::to_string(price)), web::http::methods::PUT);
    payload = check_success(json);
    assert(payload.size() == 0);

    json = get_response_after_authentication(b5.append_path(URL_QUOTE).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    payload = check_success(json);
    auto lastsaleprice_later = payload[KEY_LASTSALEPRICE].as_integer();

    json = get_response_after_authentication(b6.append_path(URL_TRADER), web::http::methods::GET);
    payload = check_success(json);
    auto balancecash_later = payload[KEY_BALANCECASH].as_integer();

    json = get_response_after_authentication(b7.append_path(URL_PORTFOLIO).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    payload = check_success(json);
    auto quantity_after = payload[KEY_QUANTITY].as_integer();
    auto totalcost_after = payload[KEY_TOTALCOST].as_integer();

    json = get_response_after_authentication(b8.append_path(URL_TRANSACTIONS), web::http::methods::GET);
    web::json::array records = json[KEY_PAYLOAD][KEY_RECORDS].as_array();

    bool found = false;
    for(auto i=records.begin(); i!=records.end(); i++) {
        auto record = i->as_object();
        auto action = record[KEY_ACTION].as_integer();
        auto status = record[KEY_STATUS].as_integer();
        if(action == ACTION_SELL && status == STATUS_EXECUTED) {
            found = true;
            break;
        }
    }
    
    assert(found == true);
    assert(price == lastsaleprice_later);
    assert(balancecash+q*price == balancecash_later);

    assert(quantity-q == quantity_after);
    assert(totalcost-q*price == totalcost_after);
}

void test_buy_pending(web::uri_builder builder) {
    web::uri_builder b1 = builder;
    web::uri_builder b2 = builder;
    web::uri_builder b3 = builder;
    web::uri_builder b4 = builder;
    web::uri_builder b5 = builder;
    web::uri_builder b6 = builder;
    web::uri_builder b7 = builder;
    web::uri_builder b8 = builder;

    auto json = get_response_after_authentication(b1.append_path(URL_QUOTE).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    auto payload = check_success(json);
    auto lastsaleprice = payload[KEY_LASTSALEPRICE].as_integer();

    json = get_response_after_authentication(b2.append_path(URL_TRADER), web::http::methods::GET);
    payload = check_success(json);
    auto balancecash = payload[KEY_BALANCECASH].as_integer();

    json = get_response_after_authentication(b3.append_path(URL_PORTFOLIO).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    payload = check_success(json);
    auto quantity = payload[KEY_QUANTITY].as_integer();
    auto totalcost = payload[KEY_TOTALCOST].as_integer();

    int q = 1;
    int price = lastsaleprice - 1;

    json = get_response_after_authentication(b4.append_path(URL_BUY).append_query(KEY_STOCKCODE, TEST_STOCKCODE1).append_query(KEY_QUANTITY, std::to_string(q)).append_query(KEY_PRICE, std::to_string(price)), web::http::methods::PUT);
    payload = check_success(json);
    assert(payload.size() == 0);

    json = get_response_after_authentication(b5.append_path(URL_QUOTE).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    payload = check_success(json);
    auto lastsaleprice_later = payload[KEY_LASTSALEPRICE].as_integer();

    json = get_response_after_authentication(b6.append_path(URL_TRADER), web::http::methods::GET);
    payload = check_success(json);
    auto balancecash_later = payload[KEY_BALANCECASH].as_integer();

    json = get_response_after_authentication(b7.append_path(URL_PORTFOLIO).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    payload = check_success(json);
    auto quantity_after = payload[KEY_QUANTITY].as_integer();
    auto totalcost_after = payload[KEY_TOTALCOST].as_integer();

    json = get_response_after_authentication(b8.append_path(URL_TRANSACTIONS), web::http::methods::GET);
    web::json::array records = json[KEY_PAYLOAD][KEY_RECORDS].as_array();

    bool found = false;
    for(auto i=records.begin(); i!=records.end(); i++) {
        auto record = i->as_object();
        auto action = record[KEY_ACTION].as_integer();
        auto status = record[KEY_STATUS].as_integer();
        if(action == ACTION_BUY && status == STATUS_PENDING) {
            found = true;
            break;
        }
    }
    
    assert(found == true);
    assert(lastsaleprice == lastsaleprice_later);
    assert(balancecash == balancecash_later);

    assert(quantity == quantity_after);
    assert(totalcost == totalcost_after);
}

void test_buy_executed(web::uri_builder builder) {
    web::uri_builder b1 = builder;
    web::uri_builder b2 = builder;
    web::uri_builder b3 = builder;
    web::uri_builder b4 = builder;
    web::uri_builder b5 = builder;
    web::uri_builder b6 = builder;
    web::uri_builder b7 = builder;
    web::uri_builder b8 = builder;

    auto json = get_response_after_authentication(b1.append_path(URL_QUOTE).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    auto payload = check_success(json);
    auto lastsaleprice = payload[KEY_LASTSALEPRICE].as_integer();

    json = get_response_after_authentication(b2.append_path(URL_TRADER), web::http::methods::GET);
    payload = check_success(json);
    auto balancecash = payload[KEY_BALANCECASH].as_integer();

    json = get_response_after_authentication(b3.append_path(URL_PORTFOLIO).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    payload = check_success(json);
    auto quantity = payload[KEY_QUANTITY].as_integer();
    auto totalcost = payload[KEY_TOTALCOST].as_integer();

    int q = 1;
    int price = lastsaleprice + 1;

    json = get_response_after_authentication(b4.append_path(URL_BUY).append_query(KEY_STOCKCODE, TEST_STOCKCODE1).append_query(KEY_QUANTITY, std::to_string(q)).append_query(KEY_PRICE, std::to_string(price)), web::http::methods::PUT);
    payload = check_success(json);
    assert(payload.size() == 0);

    json = get_response_after_authentication(b5.append_path(URL_QUOTE).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    payload = check_success(json);
    auto lastsaleprice_later = payload[KEY_LASTSALEPRICE].as_integer();

    json = get_response_after_authentication(b6.append_path(URL_TRADER), web::http::methods::GET);
    payload = check_success(json);
    auto balancecash_later = payload[KEY_BALANCECASH].as_integer();

    json = get_response_after_authentication(b7.append_path(URL_PORTFOLIO).append_query(KEY_STOCKCODE, TEST_STOCKCODE1), web::http::methods::GET);
    payload = check_success(json);
    auto quantity_after = payload[KEY_QUANTITY].as_integer();
    auto totalcost_after = payload[KEY_TOTALCOST].as_integer();

    json = get_response_after_authentication(b8.append_path(URL_TRANSACTIONS), web::http::methods::GET);
    web::json::array records = json[KEY_PAYLOAD][KEY_RECORDS].as_array();

    bool found = false;
    for(auto i=records.begin(); i!=records.end(); i++) {
        auto record = i->as_object();
        auto action = record[KEY_ACTION].as_integer();
        auto status = record[KEY_STATUS].as_integer();
        if(action == ACTION_BUY && status == STATUS_EXECUTED) {
            found = true;
            break;
        }
    }
    
    assert(found == true);
    assert(price == lastsaleprice_later);
    assert(balancecash-q*price == balancecash_later);

    assert(quantity+q == quantity_after);
    assert(totalcost+q*price == totalcost_after);
}

void test_buy_executed_new_portfolio(web::uri_builder builder) {
    web::uri_builder b1 = builder;
    web::uri_builder b2 = builder;
    web::uri_builder b3 = builder;
    web::uri_builder b4 = builder;
    web::uri_builder b5 = builder;
    web::uri_builder b6 = builder;
    web::uri_builder b7 = builder;
    web::uri_builder b8 = builder;

    auto json = get_response_after_authentication(b1.append_path(URL_QUOTE).append_query(KEY_STOCKCODE, TEST_STOCKCODE3), web::http::methods::GET);
    auto payload = check_success(json);
    auto lastsaleprice = payload[KEY_LASTSALEPRICE].as_integer();

    json = get_response_after_authentication(b2.append_path(URL_TRADER), web::http::methods::GET);
    payload = check_success(json);
    auto balancecash = payload[KEY_BALANCECASH].as_integer();

    json = get_response_after_authentication(b3.append_path(URL_PORTFOLIO).append_query(KEY_STOCKCODE, TEST_STOCKCODE3), web::http::methods::GET);
    check_error(json, 17, "Record Not Found: Portfolio");

    int q = 1;
    int price = lastsaleprice + 1;

    json = get_response_after_authentication(b4.append_path(URL_BUY).append_query(KEY_STOCKCODE, TEST_STOCKCODE3).append_query(KEY_QUANTITY, std::to_string(q)).append_query(KEY_PRICE, std::to_string(price)), web::http::methods::PUT);
    payload = check_success(json);
    assert(payload.size() == 0);

    json = get_response_after_authentication(b5.append_path(URL_QUOTE).append_query(KEY_STOCKCODE, TEST_STOCKCODE3), web::http::methods::GET);
    payload = check_success(json);
    auto lastsaleprice_later = payload[KEY_LASTSALEPRICE].as_integer();

    json = get_response_after_authentication(b6.append_path(URL_TRADER), web::http::methods::GET);
    payload = check_success(json);
    auto balancecash_later = payload[KEY_BALANCECASH].as_integer();

    json = get_response_after_authentication(b7.append_path(URL_PORTFOLIO).append_query(KEY_STOCKCODE, TEST_STOCKCODE3), web::http::methods::GET);
    payload = check_success(json);
    auto quantity_after = payload[KEY_QUANTITY].as_integer();
    auto totalcost_after = payload[KEY_TOTALCOST].as_integer();

    json = get_response_after_authentication(b8.append_path(URL_TRANSACTIONS), web::http::methods::GET);
    web::json::array records = json[KEY_PAYLOAD][KEY_RECORDS].as_array();

    bool found = false;
    for(auto i=records.begin(); i!=records.end(); i++) {
        auto record = i->as_object();
        auto action = record[KEY_ACTION].as_integer();
        auto status = record[KEY_STATUS].as_integer();
        if(action == ACTION_BUY && status == STATUS_EXECUTED) {
            found = true;
            break;
        }
    }
    
    assert(found == true);
    assert(price == lastsaleprice_later);
    assert(balancecash-q*price == balancecash_later);

    assert(q == quantity_after);
    assert(q*price == totalcost_after);
}

#ifdef _WIN32
int wmain(int argc, wchar_t *argv[])
#else
int main(int argc, char *argv[])
#endif
{
    std::string protocol = "http";
    std::string ip = "localhost";
    std::string port = "34568";
    std::string path = "/exchange";

    std::string address = "";

    address.append(protocol);
    address.append("://");
    address.append(ip);
    address.append(":");
    address.append(port);
    address.append(path);

    web::uri uri = web::uri(address);
    web::uri_builder builder(uri);

    std::map<std::string, testcase> test_map;
    test_map["test_path_missing_get"] = test_path_missing_get;
    test_map["test_path_missing_post"] = test_path_missing_post;
    test_map["test_path_missing_put"] = test_path_missing_put;
    test_map["test_path_missing_del"] = test_path_missing_del;
    test_map["test_path_not_found_get"] = test_path_not_found_get;
    test_map["test_path_not_found_post"] = test_path_not_found_post;
    test_map["test_path_not_found_put"] = test_path_not_found_put;
    test_map["test_path_not_found_del"] = test_path_not_found_del;
    test_map["test_parameter_missing_username_trader"] = test_parameter_missing_username_trader;
    test_map["test_parameter_missing_password_trader"] = test_parameter_missing_password_trader;
    test_map["test_authentication_failed_trader"] = test_authentication_failed_trader;
    test_map["test_parameter_missing_username_quote"] = test_parameter_missing_username_quote;
    test_map["test_parameter_missing_password_quote"] = test_parameter_missing_password_quote;
    test_map["test_authentication_failed_quote"] = test_authentication_failed_quote;
    test_map["test_parameter_missing_username_portfolio"] = test_parameter_missing_username_portfolio;
    test_map["test_parameter_missing_password_portfolio"] = test_parameter_missing_password_portfolio;
    test_map["test_authentication_failed_portfolio"] = test_authentication_failed_portfolio;
    test_map["test_parameter_missing_username_transactions"] = test_parameter_missing_username_transactions;
    test_map["test_parameter_missing_password_transactions"] = test_parameter_missing_password_transactions;
    test_map["test_authentication_failed_transactions"] = test_authentication_failed_transactions;
    test_map["test_parameter_missing_username_portfoliolist"] = test_parameter_missing_username_portfoliolist;
    test_map["test_parameter_missing_password_portfoliolist"] = test_parameter_missing_password_portfoliolist;
    test_map["test_authentication_failed_portfoliolist"] = test_authentication_failed_portfoliolist;
    test_map["test_parameter_missing_username_register"] = test_parameter_missing_username_register;
    test_map["test_parameter_missing_password_register"] = test_parameter_missing_password_register;
    test_map["test_parameter_missing_username_login"] = test_parameter_missing_username_login;
    test_map["test_parameter_missing_password_login"] = test_parameter_missing_password_login;
    test_map["test_authentication_failed_login"] = test_authentication_failed_login;
    test_map["test_parameter_missing_username_sell"] = test_parameter_missing_username_sell;
    test_map["test_parameter_missing_password_sell"] = test_parameter_missing_password_sell;
    test_map["test_authentication_failed_sell"] = test_authentication_failed_sell;
    test_map["test_parameter_missing_username_buy"] = test_parameter_missing_username_buy;
    test_map["test_parameter_missing_password_buy"] = test_parameter_missing_password_buy;
    test_map["test_authentication_failed_buy"] = test_authentication_failed_buy;
    test_map["test_parameter_missing_stockcode_quote"] = test_parameter_missing_stockcode_quote;
    test_map["test_record_not_found_stock_quote"] = test_record_not_found_stock_quote;
    test_map["test_parameter_missing_stockcode_portfolio"] = test_parameter_missing_stockcode_portfolio;
    test_map["test_record_not_found_portfolio_portfolio"] = test_record_not_found_portfolio_portfolio;
    test_map["test_trader_already_registered_register"] = test_trader_already_registered_register;
    test_map["test_parameter_missing_stockcode_sell"] = test_parameter_missing_stockcode_sell;
    test_map["test_parameter_missing_quantity_sell"] = test_parameter_missing_quantity_sell;
    test_map["test_parameter_missing_price_sell"] = test_parameter_missing_price_sell;
    test_map["test_parameter_invalid_quantity_sell"] = test_parameter_invalid_quantity_sell;
    test_map["test_parameter_invalid_price_sell"] = test_parameter_invalid_price_sell;
    test_map["test_parameter_missing_stockcode_buy"] = test_parameter_missing_stockcode_buy;
    test_map["test_parameter_missing_quantity_buy"] = test_parameter_missing_quantity_buy;
    test_map["test_parameter_missing_price_buy"] = test_parameter_missing_price_buy;
    test_map["test_parameter_invalid_quantity_buy"] = test_parameter_invalid_quantity_buy;
    test_map["test_parameter_invalid_price_buy"] = test_parameter_invalid_price_buy;
    test_map["test_record_not_found_stock_sell"] = test_record_not_found_stock_sell;
    test_map["test_record_not_found_portfolio_sell"] = test_record_not_found_portfolio_sell;
    test_map["test_not_enough_portfolio_quantity_sell"] = test_not_enough_portfolio_quantity_sell;
    test_map["test_record_not_found_stock_buy"] = test_record_not_found_stock_buy;
    test_map["test_not_enough_trader_balancecash_buy"] = test_not_enough_trader_balancecash_buy;
    test_map["test_trader"] = test_trader;
    test_map["test_quote1"] = test_quote1;
    test_map["test_quote2"] = test_quote2;
    test_map["test_quote3"] = test_quote3;
    test_map["test_portfolio1"] = test_portfolio1;
    test_map["test_portfolio2"] = test_portfolio2;
    test_map["test_transactions"] = test_transactions;
    test_map["test_portfoliolist"] = test_portfoliolist;
    test_map["test_register"] = test_register;
    test_map["test_login"] = test_login;
    test_map["test_sell_pending"] = test_sell_pending;
    test_map["test_sell_executed"] = test_sell_executed;
    test_map["test_buy_pending"] = test_buy_pending;
    test_map["test_buy_executed"] = test_buy_executed;

    std::cout << "START" << std::endl;

    int counter = 0;
    int size = test_map.size();
    for(auto i=test_map.begin(); i!=test_map.end(); i++) {
        counter++;
        std::cout << "(" << counter << "/" << size << ") ";
        std::cout << i->first << "...";
        try {
            i->second(builder);
        } catch(std::exception &e) {
            std::cerr << std::endl;
            std::cerr << "TESTS failed" << std::endl;
            std::cerr << "Error Description: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << "OK" << std::endl;
    }

    std::cout << "SUCCESS" << std::endl;
}
