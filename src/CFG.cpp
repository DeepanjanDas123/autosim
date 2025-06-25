#include "automata/CFG.h"

namespace automata {

CFG::CFG(const std::unordered_set<Symbol>& variables,
         const std::unordered_set<Symbol>& terminals,
         const std::unordered_map<Symbol, Productions>& productions,
         const Symbol& startSymbol)
    : variables_(variables), terminals_(terminals), productions_(productions),
      startSymbol_(startSymbol) {}

bool CFG::isValidDerivation(const std::vector<Symbol>& input, int maxDepth) const {
    std::vector<Symbol> sentential = {startSymbol_};
    return derive(sentential, input, 0, maxDepth);
}

bool CFG::derive(std::vector<Symbol>& sentential, const std::vector<Symbol>& input, int depth, int maxDepth) const {
    if (depth > maxDepth) return false;
    if (sentential.empty() && input.empty()) return true;
    if (sentential.empty() || input.empty()) return false;

    if (terminals_.count(sentential[0])) {
        if (sentential[0] == input[0]) {
            auto nextSentential = sentential;
            nextSentential.erase(nextSentential.begin());
            auto nextInput = input;
            nextInput.erase(nextInput.begin());
            return derive(nextSentential, nextInput, depth, maxDepth);
        }
        return false;
    }
    auto var = sentential[0];
    auto it = productions_.find(var);
    if (it != productions_.end()) {
        for (const auto& prod : it->second) {
            auto nextSentential = sentential;
            nextSentential.erase(nextSentential.begin());
            nextSentential.insert(nextSentential.begin(), prod.begin(), prod.end());
            if (derive(nextSentential, input, depth + 1, maxDepth))
                return true;
        }
    }
    return false;
}

} // namespace automata