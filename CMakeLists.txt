cmake_minimum_required(VERSION 3.10)
project(automata)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(automata
    src/DFA.cpp
    src/NFA.cpp
    src/Regex.cpp
    src/CFG.cpp
    src/PDA.cpp
)