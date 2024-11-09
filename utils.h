#pragma once

#include "IPaddress.h"
#include <string>
#include <regex>
#include <optional>
#include <set>
#include <sstream>


inline std::optional<std::string> extract_ip(const std::string& input) {
    std::regex ip_regex(R"(\b(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})\b)");
    std::smatch match;

    if (std::regex_search(input, match, ip_regex)) {
        std::string res = match[0];
        
        if (static_cast<size_t>(match[0].length()) != input.length()) {
            return std::nullopt;
        }

        std::stringstream ss(res);
        std::string octet;

        for (int i = 0; i < 4; ++i) {
            std::getline(ss, octet, '.');
            int octet_value = std::stoi(octet);
            if (octet_value < 0 || octet_value > 255) {
                return std::nullopt;
            }
        }
        return res;
    }

    return std::nullopt;
}

// void filter_and_print(const ip_filter::IPAddressList& ip_list, const std::function<bool(const ip_filter::IPAddress&)>& predicate) {
//     auto custom_filtered_ips = ip_list.filter(predicate);

//     for (const auto& ip : custom_filtered_ips) {
//         std::cout << ip << std::endl;
//     }
// }

// std::vector<ip_filter::IPAddress> filter_first_and_second_byte(const std::multiset<ip_filter::IPAddress, ip_filter::ReverseIPCompare>& ip_addresses, int first_byte, int second_byte) {
//     std::vector<ip_filter::IPAddress> result;
//     for (const auto& addr : ip_addresses) {
//         if (addr.get_octets()[0] == first_byte && addr.get_octets()[1] == second_byte) {
//             result.push_back(addr);
//         }
//     }
//     return result;
// }
