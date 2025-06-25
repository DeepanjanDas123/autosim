# A Comprehensive Guide to Automata and Computation Theory

A modular C++ library for automata theory, including:

- DFA
- NFA (and ε-NFA)
- Regex (interface)
- CFG (Context-Free Grammar)
- PDA (Push Down Automaton)

## Structure

- `include/automata/`: Public headers
- `src/`: Implementations
- `CMakeLists.txt`: CMake Lists file
- `other files`: some common functionalities and algorithms (transformation and certification) implemented using the library

## Features

- Clean, extensible interfaces for each automaton type
- Ready for future algorithms: minimization, transformations, parsing, etc.

## Building

```bash
mkdir build && cd build
cmake ..
make
```

## Usage Example

```cpp
#include <automata/DFA.h>
// Construct and use DFA as shown in the headers
```

## License

MIT
