/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:35:05
 * @modify date 2023-03-19 13:17:41
 */
// local
#include "solver/node.h"

#include <utility>

namespace solver {

/////////////////////////////////////
//  PNS Node Class
/////////////////////////////////////
namespace pns {

Node::Node(const Game &game)
    : game_(game), is_expanded_(false) {
  id_ = game_.toString();
}

// Node::Node(const Game &game, const Pos &pos, uint8_t value, std::shared_ptr<Node> parent)
//     : game_(game), is_expanded_(false), parent_(std::move(parent)) {
//   move_ = {pos, value};
//   game_.unsafePlay(pos, value);
//   type_ = game_.to_play_;
//   id_   = game_.toString();
// }

Node::Node(const Game &game, const Pos &pos, uint8_t value, helper::PLAYER to_play, Node *parent)
    : game_(game), is_expanded_(false), type_(to_play), parent_(parent) {
  // order matters!
  move_ = {pos, value};
  // type_ = game_.to_play_;

  game_.unsafePlay(pos, value);
  id_ = game_.toString();
}

void Node::evaluate(helper::PLAYER root_player) {
  // TODO: this doesn't feels right
  std::cerr << "  evaluating " << id_ << ", to-play = " << game_.to_play_ << ", root_player = " << root_player << ", type = " << type_ << std::endl;
  if (game_.isTerminal()) {
    // if (game_.to_play_ == root_player) {
    //   value_ = helper::PROOF_VALUE::LOSS;
    // } else {
    //   value_ = helper::PROOF_VALUE::WIN;
    // }

    // if (type_ == root_player)   {
    // value_ = (game_.to_play_ == root_player) ? helper::PROOF_VALUE::LOSS : helper::PROOF_VALUE::WIN;
    // } else {
    // value_ = (game_.to_play_ == root_player) ? helper::PROOF_VALUE::WIN : helper::PROOF_VALUE::LOSS;
    // }
    // value_ = (game_.to_play_ == root_player) ? helper::PROOF_VALUE::WIN : helper::PROOF_VALUE::LOSS;

    value_ = (type_ == helper::PLAYER::BLACK) ? helper::PROOF_VALUE::LOSS : helper::PROOF_VALUE::WIN;
  } else {
    value_ = helper::PROOF_VALUE::UNKNOWN;
  }
}

void Node::generateChildren() {
  if (is_expanded_) {
    return;
  }
  // is_expanded_ = true;

  auto possible_moves = game_.getPossibleMoves();

  // https://stackoverflow.com/questions/19562103/uint8-t-cant-be-printed-with-cout
  std::cerr << "getting possible moves for " << game_.toString() << std::endl;
  for (auto &pm : possible_moves) {
    for (auto &v : pm.second)
      std::cerr << +pm.first.row << "," << +pm.first.col << " = " << +v << std::endl;
  }

  Node *parent_ptr = this;
  for (auto &possible_move : possible_moves) {
    for (auto &value : possible_move.second) {
      // std::shared_ptr<Node> p = std::make_shared<Node>(*this);  // convert from Node to std::shared_ptr<Node>
      // children_.emplace_back(game_, possible_move.first, value, p);
      children_.emplace_back(game_, possible_move.first, value, getOpponent(type_), parent_ptr);
    }
  }

  std::cerr << "children = ";
  for (auto &c : children_) {
    std::cerr << &c << " ";
  }
  std::cerr << std::endl;
}

}  // namespace pns

/////////////////////////////////////
//  DFPN Node Class
/////////////////////////////////////
namespace dfpn {

Node::Node(const Game &game)
    : game_(game), phi_(INF), delta_(INF), is_expanded_(false) {
  id_ = game_.toString();
}

Node::Node(const Game &game, const Pos &pos, uint8_t value)
    : game_(game), phi_(1), delta_(1), is_expanded_(false) {
  move_ = {pos, value};
  game_.unsafePlay(pos, value);
  id_ = game_.toString();
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
  is_expanded_ = true;

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
  game_.unsafePlay(pos, value);
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
  is_expanded_ = true;

  auto possible_moves = game_.getPossibleMoves();
  for (auto &possible_move : possible_moves) {
    for (auto &value : possible_move.second) {
      children_.emplace_back(game_, possible_move.first, value);
    }
  }
}

//////////////////////////////////////////

NodeTT::NodeTT(const Game &game) : Node(game) {
  id_ = game_.toString();
}

NodeTT::NodeTT(const Game &game, const Pos &pos, uint8_t value) : Node(game, pos, value) {
  id_ = game_.toString();
}

// TODO: combine Node and NodeTT's generateChildren with template
void NodeTT::generateChildren() {
  if (is_expanded_) {
    return;
  }
  is_expanded_ = true;

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
  game_.unsafePlay(pos, value);
}

void Node::generateChildren() {
  if (is_expanded_) {
    return;
  }
  is_expanded_ = true;

  auto possible_moves = game_.getPossibleMoves();
  for (auto &possible_move : possible_moves) {
    for (auto &value : possible_move.second) {
      children_.emplace_back(game_, possible_move.first, value);
    }
  }
}

//////////////////////////////////////////

NodeTT::NodeTT(const Game &game) : Node(game) {
  id_ = game_.toString();
}

NodeTT::NodeTT(const Game &game, const Pos &pos, uint8_t value) : Node(game, pos, value) {
  id_ = game_.toString();
}

// TODO: combine Node and NodeTT's generateChildren with template
void NodeTT::generateChildren() {
  if (is_expanded_) {
    return;
  }
  is_expanded_ = true;

  auto possible_moves = game_.getPossibleMoves();
  for (auto &possible_move : possible_moves) {
    for (auto &value : possible_move.second) {
      children_.emplace_back(game_, possible_move.first, value);
    }
  }
}

}  // namespace negamax

}  // namespace solver
