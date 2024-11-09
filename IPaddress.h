#pragma once

#include "utils.h"
#include <array>
#include <set>
#include <sstream>
#include <string>
#include <vector>


namespace ip_filter {

class IPAddress final {
public:
    explicit IPAddress(const std::string& ip);
    bool operator<(const IPAddress& other) const;
    const std::array<int, 4>& get_octets() const;
    friend std::ostream& operator<<(std::ostream& os, const IPAddress& ip);

private:
    std::array<int, 4> octets;
    bool is_valid_octet(const std::string& octet) const;
};

struct ReverseIPCompare {
    bool operator()(const IPAddress& a, const IPAddress& b) const {
        return a.get_octets() > b.get_octets();
    }
};

class IPAddressList final {
public:
    IPAddressList();
    bool add_ip_address(const std::string& ip_address);
    const std::multiset<IPAddress, ReverseIPCompare>& get_ip_addresses() const;
    std::vector<IPAddress> filter(const std::function<bool(const IPAddress&)>& predicate) const;
    void filter_and_print(const std::function<bool(const IPAddress&)>& predicate) const;
    friend std::ostream& operator<<(std::ostream& os, const IPAddressList& ip_list);

private:
    std::multiset<IPAddress, ReverseIPCompare> ip_addresses_;
};

}; // namespace