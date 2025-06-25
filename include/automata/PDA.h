#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

namespace automata {

class PDA {
public:
    using State = std::string;
    using Symbol = char;
    using StackSymbol = char;
    using StateSet = std::unordered_set<State>;

    struct TransitionKey {
        State state;
        Symbol input;
        StackSymbol stackTop;
        bool operator==(const TransitionKey& other) const {
            return state == other.state && input == other.input && stackTop == other.stackTop;
        }
    };

    struct TransitionKeyHash {
        std::size_t operator()(const TransitionKey& k) const {
            return std::hash<std::string>()(k.state) ^ (std::hash<Symbol>()(k.input) << 1) ^ (std::hash<StackSymbol>()(k.stackTop) << 2);
        }
    };

    using TransitionValue = std::pair<State, std::vector<StackSymbol>>;
    using Transition = std::unordered_map<TransitionKey, std::vector<TransitionValue>, TransitionKeyHash>;

    PDA(const StateSet& states,
        const std::unordered_set<Symbol>& inputAlphabet,
        const std::unordered_set<StackSymbol>& stackAlphabet,
        const Transition& transition,
        const State& startState,
        StackSymbol startStack,
        const StateSet& acceptStates);

    bool accepts(const std::string& input) const;

private:
    StateSet states_;
    std::unordered_set<Symbol> inputAlphabet_;
    std::unordered_set<StackSymbol> stackAlphabet_;
    Transition transition_;
    State startState_;
    StackSymbol startStack_;
    StateSet acceptStates_;
};

} // namespace automata