#define BOOST_TEST_MODULE TestMultisetSorting
#include <boost/test/unit_test.hpp>
#include <set>
#include "../IPaddress.h"

BOOST_AUTO_TEST_SUITE(TestMultisetSorting)

BOOST_AUTO_TEST_CASE(TestReverseSorting) {
    using IP = ip_filter::IPAddress;
    using IP_Reverse = ip_filter::ReverseIPCompare;

    std::multiset<IP, IP_Reverse> ip_addresses;
    ip_addresses.insert(IP("192.168.0.1"));
    ip_addresses.insert(IP("10.0.0.1"));
    ip_addresses.insert(IP("172.16.0.1"));

    auto it = ip_addresses.begin();

    // Проверка первого IP
    std::array<int, 4> expected_octets_1{{192, 168, 0, 1}};
    BOOST_CHECK(it->get_octets() == expected_octets_1);

    // Проверка второго IP
    ++it;
    std::array<int, 4> expected_octets_2{{172, 16, 0, 1}};
    BOOST_CHECK(it->get_octets() == expected_octets_2);

    // Проверка третьего IP
    ++it;
    std::array<int, 4> expected_octets_3{{10, 0, 0, 1}};
    BOOST_CHECK(it->get_octets() == expected_octets_3);
}

BOOST_AUTO_TEST_SUITE_END()
