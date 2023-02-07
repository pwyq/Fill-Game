#pragma once

#include "game.h"

class Node {
public:
    explicit Node(const Game& game);

    Node(const Game& game, const Pos& pos, uint8_t value);

    Move move;
    bool is_expanded;
    uint32_t phi;
    uint32_t delta;
    std::string id;
    Game game;
    std::vector<Node> children{};

    void evaluate();

    void generateChildren();
};
