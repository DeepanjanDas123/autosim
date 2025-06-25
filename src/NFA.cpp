#include "automata/NFA.h"
#include <queue>

namespace automata {

NFA::NFA(const StateSet& states,
         const std::unordered_set<Symbol>& alphabet,
         const Transition& transition,
         const State& startState,
         const StateSet& acceptStates)
    : states_(states), alphabet_(alphabet), transition_(transition),
      startState_(startState), acceptStates_(acceptStates) {}

bool NFA::accepts(const std::string& input) const {
    StateSet currentStates = {startState_};
    for (auto ch : input) {
        StateSet nextStates;
        for (const auto& state : currentStates) {
            auto it = transition_.find({state, ch});
            if (it != transition_.end())
                nextStates.insert(it->second.begin(), it->second.end());
        }
        currentStates = nextStates;
    }
    for (const auto& state : currentStates)
        if (acceptStates_.count(state)) return true;
    return false;
}

EpsilonNFA::EpsilonNFA(const StateSet& states,
                       const std::unordered_set<Symbol>& alphabet,
                       const Transition& transition,
                       const State& startState,
                       const StateSet& acceptStates)
    : NFA(states, alphabet, transition, startState, acceptStates) {}

auto EpsilonNFA::epsilonClosure(const StateSet& states) const -> StateSet {
    StateSet closure = states;
    std::queue<State> q;
    for (const auto& s : states) q.push(s);

    while (!q.empty()) {
        State s = q.front(); q.pop();
        auto it = transition_.find({s, '\0'});
        if (it != transition_.end()) {
            for (const auto& t : it->second)
                if (closure.insert(t).second) q.push(t);
        }
    }
    return closure;
}

bool EpsilonNFA::accepts(const std::string& input) const {
    StateSet currentStates = epsilonClosure({startState_});
    for (auto ch : input) {
        StateSet nextStates;
        for (const auto& state : currentStates) {
            auto it = transition_.find({state, ch});
            if (it != transition_.end())
                nextStates.insert(it->second.begin(), it->second.end());
        }
        currentStates = epsilonClosure(nextStates);
    }
    for (const auto& state : currentStates)
        if (acceptStates_.count(state)) return true;
    return false;
}

} // namespace automata