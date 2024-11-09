#define BOOST_TEST_MODULE test_ip_address
#include <boost/test/unit_test.hpp>
#include "../IPaddress.h"

BOOST_AUTO_TEST_SUITE(test_ip_address)

BOOST_AUTO_TEST_CASE(TestValidIPAddress) {
    ip_filter::IPAddress ip("192.168.1.1");
    BOOST_CHECK(ip.get_octets() == (std::array<int, 4>{{192, 168, 1, 1}}));
}

BOOST_AUTO_TEST_CASE(TestInvalidIPAddress) {
    BOOST_CHECK_THROW(ip_filter::IPAddress("300.1.1.1"), std::invalid_argument);
    BOOST_CHECK_THROW(ip_filter::IPAddress("192.168.1"), std::invalid_argument);
    BOOST_CHECK_THROW(ip_filter::IPAddress("192.168.1.1.1"), std::invalid_argument);
    BOOST_CHECK_THROW(ip_filter::IPAddress("abc.def.ghi.jkl"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(TestOutputStream) {
    ip_filter::IPAddress ip("192.168.0.1");
    std::stringstream ss;
    ss << ip;
    BOOST_CHECK_EQUAL(ss.str(), "192.168.0.1");
}

BOOST_AUTO_TEST_SUITE_END()
