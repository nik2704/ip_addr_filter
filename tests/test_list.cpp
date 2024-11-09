#define BOOST_TEST_MODULE TestIPAddressListSorting
#include <boost/test/unit_test.hpp>
#include <set>
#include "../IPaddress.h"

BOOST_AUTO_TEST_SUITE(TestIPAddressListSorting)

BOOST_AUTO_TEST_CASE(TestReverseSorting) {
    using IPAddressList = ip_filter::IPAddressList;

    IPAddressList ip_list;
    ip_list.add_ip_address("192.168.0.1");
    ip_list.add_ip_address("10.0.0.1");
    ip_list.add_ip_address("172.16.0.1");

    auto it = ip_list.get_ip_addresses().begin();

    std::array<int, 4> expected_octets_1{{192, 168, 0, 1}};
    BOOST_CHECK(it->get_octets() == expected_octets_1);

    ++it;
    std::array<int, 4> expected_octets_2{{172, 16, 0, 1}};
    BOOST_CHECK(it->get_octets() == expected_octets_2);

    ++it;
    std::array<int, 4> expected_octets_3{{10, 0, 0, 1}};
    BOOST_CHECK(it->get_octets() == expected_octets_3);
}

BOOST_AUTO_TEST_SUITE_END()
