/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:35:05
 * @modify date 2023-02-10 05:35:05
 */
// local
#include "solver/node.h"

namespace solver {

/////////////////////////////////////
//  DFPN Node Class
/////////////////////////////////////
namespace dfpn {

Node::Node(const Game &game)
    : game_(game), phi_(INF), delta_(INF), is_expanded_(false) {
  id_ = this->game_.toString();
}

Node::Node(const Game &game, const Pos &pos, uint8_t value)
    : game_(game), phi_(1), delta_(1), is_expanded_(false) {
  move_ = {pos, value};
  this->game_.unsafePlay(pos, value);
  id_ = this->game_.toString();
  evaluate();
}

void Node::evaluate() {
  if (game_.isTerminal()) {
    phi_   = INF;
    delta_ = 0;
  } else {
    phi_   = 1;
    delta_ = 1;
  }
}

void Node::generateChildren() {
  if (is_expanded_) {
    return;
  }
  is_expanded_        = true;
  auto possible_moves = game_.getPossibleMoves();
  for (auto &possible_move : possible_moves) {
    for (auto &value : possible_move.second) {
      children_.emplace_back(game_, possible_move.first, value);
    }
  }
}
}  // namespace dfpn

/////////////////////////////////////
//  Minimax Node Class
/////////////////////////////////////
namespace minimax {

Node::Node(const Game &game)
    : game_(game), is_expanded_(false) {
}

Node::Node(const Game &game, const Pos &pos, uint8_t value)
    : game_(game), is_expanded_(false) {
  move_ = {pos, value};
  this->game_.unsafePlay(pos, value);
}

/**
 * @brief Minimax evaluates from root player's view. Root is assumed to be black.
 * 
 * @param player 
 */
void Node::evaluate(helper::PLAYER player) {
  if (game_.isTerminal()) {
    eval_val_ = (player == helper::PLAYER::WHITE) ? 1 : -1;
  } else {
    eval_val_ = 0;
  }
}

void Node::generateChildren() {
  if (is_expanded_) {
    return;
  }
  is_expanded_        = true;
  auto possible_moves = game_.getPossibleMoves();
  for (auto &possible_move : possible_moves) {
    for (auto &value : possible_move.second) {
      children_.emplace_back(game_, possible_move.first, value);
    }
  }
}

}  // namespace minimax

/////////////////////////////////////
//  Negamax Node Class
//  Negamax evaluate from to-player's view, which always returns -1 at the terminal. So we don't need a specific evaluate()
/////////////////////////////////////
namespace negamax {

Node::Node(const Game &game)
    : game_(game), is_expanded_(false) {
}

Node::Node(const Game &game, const Pos &pos, uint8_t value)
    : game_(game), is_expanded_(false) {
  move_ = {pos, value};
  this->game_.unsafePlay(pos, value);
}

void Node::generateChildren() {
  if (is_expanded_) {
    return;
  }
  is_expanded_        = true;
  auto possible_moves = game_.getPossibleMoves();
  for (auto &possible_move : possible_moves) {
    for (auto &value : possible_move.second) {
      children_.emplace_back(game_, possible_move.first, value);
    }
  }
}

//////////////////////////////////////////

NodeTT::NodeTT(const Game &game) : Node(game) {
  id_ = this->game_.toString();
}

NodeTT::NodeTT(const Game &game, const Pos &pos, uint8_t value) : Node(game, pos, value) {
  id_ = this->game_.toString();
}

// TODO: combine Node and NodeTT's generateChildren with template
void NodeTT::generateChildren() {
  if (is_expanded_) {
    return;
  }
  is_expanded_        = true;
  auto possible_moves = game_.getPossibleMoves();
  for (auto &possible_move : possible_moves) {
    for (auto &value : possible_move.second) {
      children_.emplace_back(game_, possible_move.first, value);
    }
  }
}

}  // namespace negamax

}  // namespace solver
