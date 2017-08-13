#include <boost/test/unit_test.hpp>

#include "../include/model.h"

class TestModel : public Model {
protected:
	web::json::value to_json() {
		return web::json::value::object();
	}

public:
    void setExists(bool flag) {
        exists(flag);
    }
};

BOOST_AUTO_TEST_SUITE(ModelTest)

BOOST_AUTO_TEST_CASE(Constructor)
{
    TestModel test_model;
    BOOST_CHECK(test_model.exists() == false);
}

BOOST_AUTO_TEST_CASE(existsTrue)
{
    TestModel test_model;
    test_model.setExists(true);
    BOOST_CHECK(test_model.exists() == true);
}

BOOST_AUTO_TEST_CASE(existsFalse)
{
    TestModel test_model;
    test_model.setExists(false);
    BOOST_CHECK(test_model.exists() == false);
}

BOOST_AUTO_TEST_SUITE_END()
