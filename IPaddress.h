#include <array>
#include <sstream>
#include <string>

namespace ip_filter {

class IPAddress {
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

}; // namespace