#include <string>
#include <regex>
#include <optional>
#include <sstream>

std::optional<std::string> extract_ip(const std::string& input) {
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
