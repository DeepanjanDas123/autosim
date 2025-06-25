#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "include/automata/DFA.h"

int main() {
    using State = automata::DFA::State;
    using Symbol = automata::DFA::Symbol;
    using TransitionKey = automata::DFA::TransitionKey;
    using Transition = automata::DFA::Transition;

    int numStates, numSymbols, numTransitions, numAccepts;

    std::cout << "Number of states: ";
    std::cin >> numStates;
    std::unordered_set<State> states;
    std::cout << "Enter state names (one per line):\n";
    for (int i = 0; i < numStates; ++i) {
        State s;
        std::cin >> s;
        states.insert(s);
    }

    std::cout << "Number of alphabet symbols: ";
    std::cin >> numSymbols;
    std::unordered_set<Symbol> alphabet;
    std::cout << "Enter symbols (one per line):\n";
    for (int i = 0; i < numSymbols; ++i) {
        Symbol sym;
        std::cin >> sym;
        alphabet.insert(sym);
    }

    std::cout << "Number of transitions: ";
    std::cin >> numTransitions;
    Transition transitions;
    std::cout << "Enter transitions (format: from_state symbol to_state):\n";
    for (int i = 0; i < numTransitions; ++i) {
        State from, to;
        Symbol sym;
        std::cin >> from >> sym >> to;
        transitions[{from, sym}] = to;
    }

    std::cout << "Enter start state: ";
    State start;
    std::cin >> start;

    std::cout << "Number of accept states: ";
    std::cin >> numAccepts;
    std::unordered_set<State> acceptStates;
    std::cout << "Enter accept states (one per line):\n";
    for (int i = 0; i < numAccepts; ++i) {
        State s;
        std::cin >> s;
        acceptStates.insert(s);
    }

    std::cin.ignore(); // clear newline
    std::cout << "Enter input string: ";
    std::string input;
    std::getline(std::cin, input);

    automata::DFA dfa(states, alphabet, transitions, start, acceptStates);

    if (dfa.accepts(input))
        std::cout << "Accepted\n";
    else
        std::cout << "Rejected\n";

    return 0;
}

//run this with the following commands:
//g++ DFA_acceptance.cpp src/DFA.cpp -Iinclude
//./a.out