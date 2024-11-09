#define BOOST_TEST_MODULE test_utils
#include <boost/test/unit_test.hpp>
#include "../utils.h"

BOOST_AUTO_TEST_SUITE(test_utils)

BOOST_AUTO_TEST_CASE(TestValidIP) {
    BOOST_CHECK(extract_ip("192.168.1.1").has_value());
    BOOST_CHECK(extract_ip("10.0.0.255").has_value());
    BOOST_CHECK(extract_ip("172.16.0.0").has_value());
}

BOOST_AUTO_TEST_CASE(TestInvalidIP) {
    BOOST_CHECK(!extract_ip("256.256.256.256").has_value());
    BOOST_CHECK(!extract_ip("192.168.1").has_value());
    BOOST_CHECK(!extract_ip("192.168.1.1.1").has_value());
    BOOST_CHECK(!extract_ip("abc.def.ghi.jkl").has_value());
}

BOOST_AUTO_TEST_SUITE_END()
