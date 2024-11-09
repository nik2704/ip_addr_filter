#include "IPaddress.h"
#include "utils.h"
#include <iostream>
#include <sstream>
#include <set>

int main() {
    using IP_List = ip_filter::IPAddressList;
    IP_List ip_list;
    std::string line;

    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string field;

        std::getline(ss, field, '\t');
        ip_list.add_ip_address(field);
    }

    std::cout << ip_list;

    ip_list.filter_and_print([](const ip_filter::IPAddress& ip) {
        return ip.get_octets()[0] == 1;
    });
  
    ip_list.filter_and_print([](const ip_filter::IPAddress& ip) {
        return ip.get_octets()[0] == 46 && ip.get_octets()[1] == 70;
    });

    ip_list.filter_and_print([](const ip_filter::IPAddress& ip) {
        return ip.get_octets()[0] == 46 || ip.get_octets()[1] == 46 || ip.get_octets()[2] == 46 || ip.get_octets()[3] == 46;
    });

    return 0;
}
