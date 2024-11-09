#include "IPaddress.h"
#include "utils.h"
#include <iostream>
#include <sstream>
#include <set>

int main() {
    using IP = ip_filter::IPAddress;
    using IP_Reverse = ip_filter::ReverseIPCompare;

    std::multiset<IP, IP_Reverse> ip_addresses;
    std::string line;

    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string field;

        std::getline(ss, field, '\t');
        auto ipextracted = extract_ip(field);

        if (ipextracted.has_value()) {
            IP addr(ipextracted .value());
            ip_addresses.insert(addr);

        }
    }

    for (const auto& addr : ip_addresses) {
        std::cout << addr << std::endl;
    }


    return 0;
}
