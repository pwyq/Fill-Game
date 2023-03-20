# Fill-Game

[![build](https://github.com/pwyq/Fill-Game/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/pwyq/Fill-Game/actions/workflows/c-cpp.yml)

Fill-Game is a two-player (adversarial) version of [Fillomino](https://en.wikipedia.org/wiki/Fillomino). It is (probably) first proposed by [Dr. Martin Müller](https://webdocs.cs.ualberta.ca/~mmueller/); if so; this software is the first for Fill-Game.

## Functions & Goals

- [x] Local play
    - [x] Two human players
    - [x] Human vs. AI player
- [ ] Cross-machine play
- [x] Cross-platform deployment
    - [x] Linux
    - [x] Windows 
    - [ ] Mac

### Algorithms

- Depth-First Proof Number Search (DFPN)
- Minimax, (with alpha-beta pruning and transposition table)
- Negamax, (with alpha-beta pruning and transposition table)

## Build

```
# To build with GUI (requires set up Qt5.12.8)
./linux_build.sh --gui

# To build without GUI
./linux_build.sh
```

### Run

```
# Start GUI version
./fillgame_gui

# Start CLI version
./fillgame_cli <game-board-string> <time-limit>

# To test algorithms
./test_main
```

## Development

- Ubuntu 22.04
- VS Code
- C++ 20
- GUI Framework: Qt5
- Unit test: [Google Test](https://github.com/google/googletest)
- Formatter: clang-format-12
- Profiler: Valgrind, kcachegrind

### Guide
- Follows [Google C++ Guide](https://google.github.io/styleguide/cppguide.html)
- Profiler: `valgrind --tool=callgrind ./(Your binary)` && `kcachegrind callgrind.out.x`
