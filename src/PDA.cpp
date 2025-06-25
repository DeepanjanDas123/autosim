#include "automata/PDA.h"

namespace automata {

PDA::PDA(const StateSet& states,
         const std::unordered_set<Symbol>& inputAlphabet,
         const std::unordered_set<StackSymbol>& stackAlphabet,
         const Transition& transition,
         const State& startState,
         StackSymbol startStack,
         const StateSet& acceptStates)
    : states_(states), inputAlphabet_(inputAlphabet), stackAlphabet_(stackAlphabet),
      transition_(transition), startState_(startState), startStack_(startStack),
      acceptStates_(acceptStates) {}

bool PDA::accepts(const std::string& input) const {
    struct Config {
        State state;
        size_t pos;
        std::vector<StackSymbol> stack;
    };
    std::vector<Config> configs = {{startState_, 0, {startStack_}}};
    size_t step = 0, maxSteps = 10000;

    while (!configs.empty() && step++ < maxSteps) {
        std::vector<Config> nextConfigs;
        for (const auto& conf : configs) {
            if (conf.pos == input.size() && acceptStates_.count(conf.state))
                return true;
            StackSymbol top = conf.stack.empty() ? '\0' : conf.stack.back();

            // Epsilon transitions
            auto it = transition_.find({conf.state, '\0', top});
            if (it != transition_.end()) {
                for (const auto& [nextState, toPush] : it->second) {
                    auto nextStack = conf.stack;
                    if (!nextStack.empty()) nextStack.pop_back();
                    nextStack.insert(nextStack.end(), toPush.rbegin(), toPush.rend());
                    nextConfigs.push_back({nextState, conf.pos, nextStack});
                }
            }
            // Input transitions
            if (conf.pos < input.size()) {
                Symbol sym = input[conf.pos];
                it = transition_.find({conf.state, sym, top});
                if (it != transition_.end()) {
                    for (const auto& [nextState, toPush] : it->second) {
                        auto nextStack = conf.stack;
                        if (!nextStack.empty()) nextStack.pop_back();
                        nextStack.insert(nextStack.end(), toPush.rbegin(), toPush.rend());
                        nextConfigs.push_back({nextState, conf.pos + 1, nextStack});
                    }
                }
            }
        }
        configs = nextConfigs;
    }
    return false;
}

} // namespace automata