#define BOOST_TEST_MODULE TestIPAddressListFilter
#include <boost/test/unit_test.hpp>
#include <vector>
#include "../IPaddress.h"

BOOST_AUTO_TEST_SUITE(TestIPAddressListFilter)

BOOST_AUTO_TEST_CASE(TestFilterByFirstOctet) {
    using IPAddressList = ip_filter::IPAddressList;

    IPAddressList ip_list;
    ip_list.add_ip_address("192.168.0.1");
    ip_list.add_ip_address("10.0.0.1");
    ip_list.add_ip_address("46.70.1.1");

    std::vector<ip_filter::IPAddress> filtered_ips = ip_list.filter([](const ip_filter::IPAddress& ip) {
        return ip.get_octets()[0] == 46;
    });

    BOOST_CHECK_EQUAL(filtered_ips.size(), 1);
    std::array<int, 4> expected_octets{{46, 70, 1, 1}};
    BOOST_CHECK(filtered_ips[0].get_octets() == expected_octets);
}

BOOST_AUTO_TEST_SUITE_END()
