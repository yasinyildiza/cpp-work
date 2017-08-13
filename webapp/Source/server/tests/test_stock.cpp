#include <boost/test/unit_test.hpp>

#include "../include/stock.h"

BOOST_AUTO_TEST_SUITE(StockTest)

BOOST_AUTO_TEST_CASE(Constructor)
{
    Stock stock;
    BOOST_CHECK(stock.exists() == false);
}

BOOST_AUTO_TEST_CASE(to_json)
{
    std::string stockcode = "TEST_CODE";
    int lastsaleprice = 123;

    Stock stock;
    stock.stockcode = stockcode;
    stock.lastsaleprice = lastsaleprice;

    web::json::value obj = stock.to_json();

    BOOST_CHECK(obj.size() == 2);
    BOOST_CHECK(obj["stockcode"].as_string() == stockcode);
    BOOST_CHECK(obj["lastsaleprice"].as_integer() == lastsaleprice);
}

BOOST_AUTO_TEST_SUITE_END()
