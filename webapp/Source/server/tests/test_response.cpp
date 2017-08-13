#include <boost/test/unit_test.hpp>

#include "../include/response.h"

BOOST_AUTO_TEST_SUITE(ResponseTest)

BOOST_AUTO_TEST_CASE(success_with_no_argument)
{
    web::json::value obj = Response().success();

    auto success = obj["success"];
    auto payload = obj["payload"];

    BOOST_CHECK(obj.size() == 2);
    BOOST_CHECK(success.as_bool() == true);
    BOOST_CHECK(payload.size() == 0);
}

BOOST_AUTO_TEST_CASE(success_with_payload)
{
    std::string key = "test_key";
    std::string value = "test_value";
    web::json::value p = web::json::value::object();
    p[key] = web::json::value::string(value);

    web::json::value obj = Response().success(p);

    auto success = obj["success"];
    auto payload = obj["payload"];

    BOOST_CHECK(obj.size() == 2);
    BOOST_CHECK(success.as_bool() == true);
    BOOST_CHECK(payload.size() == p.size());
    BOOST_CHECK(payload[key].as_string() == value);
}

BOOST_AUTO_TEST_CASE(failure_with_error_code)
{
    ErrorCode error_code = ErrorCode::UnknownError;
    int code = (int)error_code;
    std::string message = Response::message_map[error_code];

    web::json::value obj = Response().failure(error_code);

    auto success = obj["success"];
    auto error = obj["error"];

    BOOST_CHECK(obj.size() == 2);
    BOOST_CHECK(success.as_bool() == false);
    BOOST_CHECK(error.size() == 2);
    BOOST_CHECK(error["code"].as_integer() == code);
    BOOST_CHECK(error["message"].as_string() == message);
}

BOOST_AUTO_TEST_CASE(failure_with_code_and_message)
{
    int code = 13;
    std::string message = "this is a message";

    web::json::value obj = Response().failure(code, message);

    auto success = obj["success"];
    auto error = obj["error"];

    BOOST_CHECK(obj.size() == 2);
    BOOST_CHECK(success.as_bool() == false);
    BOOST_CHECK(error.size() == 2);
    BOOST_CHECK(error["code"].as_integer() == code);
    BOOST_CHECK(error["message"].as_string() == message);
}

BOOST_AUTO_TEST_SUITE_END()
