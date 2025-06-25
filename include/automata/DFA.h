#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <utility>

namespace automata {

class DFA {
public:
    using State = std::string;
    using Symbol = char;
    using StateSet = std::unordered_set<State>;
    using TransitionKey = std::pair<State, Symbol>;

    struct TransitionKeyHash {
        std::size_t operator()(const TransitionKey& k) const {
            return std::hash<std::string>()(k.first) ^ (std::hash<Symbol>()(k.second) << 1);
        }
    };

    using Transition = std::unordered_map<TransitionKey, State, TransitionKeyHash>;

    DFA(const StateSet& states,
        const std::unordered_set<Symbol>& alphabet,
        const Transition& transition,
        const State& startState,
        const StateSet& acceptStates);

    bool accepts(const std::string& input) const;

private:
    StateSet states_;
    std::unordered_set<Symbol> alphabet_;
    Transition transition_;
    State startState_;
    StateSet acceptStates_;
};

} // namespace automata