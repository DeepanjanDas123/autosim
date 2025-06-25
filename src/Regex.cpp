#include "automata/Regex.h"

namespace automata {

Regex::Regex(const std::string& pattern)
    : pattern_(pattern), regex_(pattern_) {}

bool Regex::matches(const std::string& str) const {
    return std::regex_match(str, regex_);
}

} // namespace automata