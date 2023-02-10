# Fill-Game

[![build](https://github.com/pwyq/Fill-Game/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/pwyq/Fill-Game/actions/workflows/c-cpp.yml)

Fill-Game is a two-player (adversarial) version of [Fillomino](https://en.wikipedia.org/wiki/Fillomino). It is (probably) first proposed by [Dr. Martin Müller](https://webdocs.cs.ualberta.ca/~mmueller/); if so; this software is the first for Fill-Game.

## Functions & Goals
- [x] Local play
    - [x] Two human players
    - [x] Human vs. AI player
- [ ] Cross-machine play
- [ ] Cross-platform deployment


## Build
```
git clone --recurse-submodules https://github.com/pwyq/Fill-Game.git
```

```
./linux_build.sh
```

## Development

- Follows [Google C++ Guide](https://google.github.io/styleguide/cppguide.html)
- Formatter ` find . -iname *.h -o -iname *.cpp | xargs clang-format-12 -i`

### Environment & Tools
- Ubuntu 22.04, VS Code
- C++ 20
- Qt5
- [Google Test](https://github.com/google/googletest), clang-format-12