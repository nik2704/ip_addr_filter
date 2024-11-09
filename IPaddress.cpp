#include "IPaddress.h"
#include <algorithm>
#include <array>
#include <sstream>
#include <string>

namespace ip_filter {

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

} // namespace