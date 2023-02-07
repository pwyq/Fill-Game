#include "solver/node.h"

Node::Node(const Game& game) : 
    game(game),
    phi(INF),
    delta(INF),
    is_expanded(false)
{
    id = this->game.toString();
}

Node::Node(const Game& game, const Pos& pos, uint8_t value) : game(game), phi(1), delta(1), is_expanded(false) {
    move = {pos, value};
    this->game.unsafePlay(pos, value);
    id = this->game.toString();
    evaluate();
}

void Node::evaluate() {
    if (game.isTerminal()) {
        phi = INF;
        delta = 0;
    } else {
        phi = 1;
        delta = 1;
    }
}

void Node::generateChildren() {
    if (is_expanded) {
        return;
    }
    is_expanded = true;
    auto possible_moves = game.getPossibleMoves();
    for (auto& possible_move : possible_moves) {
        for (auto& value : possible_move.second) {
            children.emplace_back(game, possible_move.first, value);
        }
    }
}
