#pragma once
#include <string>
#include <regex>

namespace automata {

class Regex {
public:
    explicit Regex(const std::string& pattern);

    bool matches(const std::string& str) const;

private:
    std::string pattern_;
    std::regex regex_;
};

} // namespace automata