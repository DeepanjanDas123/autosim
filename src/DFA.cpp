#include "automata/DFA.h"

namespace automata {

DFA::DFA(const StateSet& states,
         const std::unordered_set<Symbol>& alphabet,
         const Transition& transition,
         const State& startState,
         const StateSet& acceptStates)
    : states_(states), alphabet_(alphabet), transition_(transition),
      startState_(startState), acceptStates_(acceptStates) {}

bool DFA::accepts(const std::string& input) const {
    State current = startState_;
    for (auto ch : input) {
        auto it = transition_.find({current, ch});
        if (it == transition_.end()) return false;
        current = it->second;
    }
    return acceptStates_.count(current) > 0;
}

} // namespace automata