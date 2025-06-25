#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

namespace automata {

class CFG {
public:
    using Symbol = std::string;
    using Production = std::vector<Symbol>;
    using Productions = std::vector<Production>;

    CFG(const std::unordered_set<Symbol>& variables,
        const std::unordered_set<Symbol>& terminals,
        const std::unordered_map<Symbol, Productions>& productions,
        const Symbol& startSymbol);

    bool isValidDerivation(const std::vector<Symbol>& input, int maxDepth = 10) const;

private:
    std::unordered_set<Symbol> variables_;
    std::unordered_set<Symbol> terminals_;
    std::unordered_map<Symbol, Productions> productions_;
    Symbol startSymbol_;
    bool derive(std::vector<Symbol>& sentential, const std::vector<Symbol>& input, int depth, int maxDepth) const;
};

} // namespace automata