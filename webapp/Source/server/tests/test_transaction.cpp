#include <boost/test/unit_test.hpp>

#include "../include/transaction.h"

BOOST_AUTO_TEST_SUITE(TransactionTest)

BOOST_AUTO_TEST_CASE(Constructor)
{
    Transaction transaction;
    BOOST_CHECK(transaction.exists() == false);
}

BOOST_AUTO_TEST_CASE(to_json)
{
    std::string username = "TEST_USERNAME";
    std::string stockcode = "TEST_CODE";
    int quantity = 123;
    int datetime = 456;
    int action = 789;
    int status = 135;

    Transaction transaction;
    transaction.username = username;
    transaction.stockcode = stockcode;
    transaction.quantity = quantity;
    transaction.datetime = datetime;
    transaction.action = action;
    transaction.status = status;

    web::json::value obj = transaction.to_json();

    BOOST_CHECK(obj.size() == 6);
    BOOST_CHECK(obj["username"].as_string() == username);
    BOOST_CHECK(obj["stockcode"].as_string() == stockcode);
    BOOST_CHECK(obj["quantity"].as_integer() == quantity);
    BOOST_CHECK(obj["datetime"].as_integer() == datetime);
    BOOST_CHECK(obj["action"].as_integer() == action);
    BOOST_CHECK(obj["status"].as_integer() == status);
}

BOOST_AUTO_TEST_SUITE_END()
