#include <boost/test/unit_test.hpp>

#include "../include/trader.h"

BOOST_AUTO_TEST_SUITE(TraderTest)

BOOST_AUTO_TEST_CASE(Constructor)
{
    Trader trader;
    BOOST_CHECK(trader.exists() == false);
}

BOOST_AUTO_TEST_CASE(to_json)
{
    std::string username = "TEST_USERNAME";
    std::string password = "TEST_PASSWORD";
    int balancecash = 123;

    Trader trader;
    trader.username = username;
    trader.password = password;
    trader.balancecash = balancecash;

    web::json::value obj = trader.to_json();

    BOOST_CHECK(obj.size() == 2);
    BOOST_CHECK(obj["username"].as_string() == username);
    //BOOST_CHECK(obj["password"].as_string() == password);
    BOOST_CHECK(obj["balancecash"].as_integer() == balancecash);
}

BOOST_AUTO_TEST_SUITE_END()
