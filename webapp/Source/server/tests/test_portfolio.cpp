#include <boost/test/unit_test.hpp>

#include "../include/portfolio.h"

BOOST_AUTO_TEST_SUITE(PortfolioTest)

BOOST_AUTO_TEST_CASE(Constructor)
{
    Portfolio portfolio;
    BOOST_CHECK(portfolio.exists() == false);
}

BOOST_AUTO_TEST_CASE(to_json)
{
    std::string username = "TEST_USERNAME";
    std::string stockcode = "TEST_CODE";
    int quantity = 123;
    int totalcost = 456;

    Portfolio portfolio;
    portfolio.username = username;
    portfolio.stockcode = stockcode;
    portfolio.quantity = quantity;
    portfolio.totalcost = totalcost;

    web::json::value obj = portfolio.to_json();

    BOOST_CHECK(obj.size() == 4);
    BOOST_CHECK(obj["username"].as_string() == username);
    BOOST_CHECK(obj["stockcode"].as_string() == stockcode);
    BOOST_CHECK(obj["quantity"].as_integer() == quantity);
    BOOST_CHECK(obj["totalcost"].as_integer() == totalcost);
}

BOOST_AUTO_TEST_SUITE_END()
