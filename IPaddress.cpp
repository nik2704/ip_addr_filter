#include "IPaddress.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>


namespace ip_filter {

//IPAddress
IPAddress::IPAddress(const std::string& ip) {
    std::stringstream ss(ip);
    std::string octet;

    for (std::size_t i = 0; i < 4; ++i) {
        if (!std::getline(ss, octet, '.')) {
            throw std::invalid_argument("Неверный формат IP-адреса: недостаточно октетов");
        }

        if (!is_valid_octet(octet)) {
            throw std::invalid_argument("Неверный октет IP-адреса: " + octet);
        }

        octets[i] = std::stoi(octet);
    }
    
    if (ss.rdbuf()->in_avail() > 0) {
        throw std::invalid_argument("Неверный формат IP-адреса: лишние символы");
    }
}

const std::array<int, 4>& IPAddress::get_octets() const {
    return octets;
}

bool IPAddress::operator<(const IPAddress& other) const {
    return octets < other.octets;
}

bool IPAddress::is_valid_octet(const std::string& octet) const {
    if (octet.empty() || octet.size() > 3) {
        return false;
    }

    for (char c : octet) {
        if (!std::isdigit(c)) {
            return false;
        }
    }

    int value = std::stoi(octet);
    
    return value >= 0 && value <= 255;
}  

std::ostream& operator<<(std::ostream& os, const IPAddress& ip) {
    os << ip.octets[0] << "." << ip.octets[1] << "." << ip.octets[2] << "." << ip.octets[3];
    return os;
}

//IPAddressList
IPAddressList::IPAddressList() = default;

bool IPAddressList::add_ip_address(const std::string& ip_address) {
    auto ipextracted = extract_ip(ip_address);

    if (ipextracted.has_value()) {
        try {
            IPAddress addr(ipextracted .value());
            ip_addresses_.insert(addr);

            return true;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return false;
}

const std::multiset<IPAddress, ReverseIPCompare>& IPAddressList::get_ip_addresses() const {
    return ip_addresses_;
}

std::vector<IPAddress> IPAddressList::filter(const std::function<bool(const IPAddress&)>& predicate) const {
    std::vector<IPAddress> result;

    for (const auto& ip : ip_addresses_) {
        if (predicate(ip)) {
            result.push_back(ip);
        }
    }

    return result;
}

void IPAddressList::filter_and_print(const std::function<bool(const IPAddress&)>& predicate) const {
    auto custom_filtered_ips = filter(predicate);

    for (const auto& ip : custom_filtered_ips) {
        std::cout << ip << std::endl;
    } 
}

std::ostream& operator<<(std::ostream& os, const IPAddressList& ip_list) {
    for (const auto& addr : ip_list.ip_addresses_) {
        os << addr << std::endl;
    }

    return os;
}

} // namespace