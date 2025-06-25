# automata

A modular C++ library for automata theory, including:

- DFA
- NFA (and ε-NFA)
- Regex (interface)
- CFG (Context-Free Grammar)
- PDA (Push Down Automaton)

## Structure

- `include/automata/`: Public headers
- `src/`: Implementations

## Features

- Clean, extensible interfaces for each automaton type
- **No Boost dependency**; only STL
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