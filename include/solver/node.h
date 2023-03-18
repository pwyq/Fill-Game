/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:31:05
 * @modify date 2023-02-10 05:31:05
 * @desc Node for Game class
 */
#ifndef FG_SOLVER_NODE_H_
#define FG_SOLVER_NODE_H_
// local
#include "game.h"

namespace solver {

/////////////////////////////////////
//  Basic Node Class
/////////////////////////////////////
// TODO: generalize?
class Node {
 public:
  Node();
};

/////////////////////////////////////
//  DFPN Node Class
/////////////////////////////////////
namespace dfpn {
class Node {
 public:
  explicit Node(const Game &game);

  // value = the number to play
  Node(const Game &game, const helper::Pos &pos, uint8_t value);

  Game game_;
  uint32_t phi_;
  uint32_t delta_;
  bool is_expanded_;

  helper::Move move_;
  std::string id_;

  std::vector<Node> children_{};

  void evaluate();
  void generateChildren();
};
}  // namespace dfpn

/////////////////////////////////////
//  Minimax Node Class
/////////////////////////////////////
namespace minimax {
class Node {
 public:
  explicit Node(const Game &game);
  Node(const Game &game, const helper::Pos &pos, uint8_t value);

  Game game_;
  int eval_val_;  // evaluation value of the node, can be positive and negative
  bool is_expanded_;
  helper::Move move_;
  std::vector<Node> children_{};

  void evaluate(helper::PLAYER player);
  void generateChildren();
};
}  // namespace minimax

/////////////////////////////////////
//  Negamax Node Class
/////////////////////////////////////
namespace negamax {
class Node {
 public:
  explicit Node(const Game &game);
  Node(const Game &game, const helper::Pos &pos, uint8_t value);

  Game game_;
  bool is_expanded_;
  helper::Move move_;
  std::vector<Node> children_{};

  void generateChildren();
};
}  // namespace negamax

}  // namespace solver

#endif  // FG_SOLVER_NODE_H_