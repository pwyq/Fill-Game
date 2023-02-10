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

class Node {
 public:
  explicit Node(const Game &game);

  Node(const Game &game, const Pos &pos, uint8_t value);

  Game game_;
  uint32_t phi_;
  uint32_t delta_;
  bool is_expanded_;

  Move move_;
  std::string id_;

  std::vector<Node> children_{};

  void evaluate();

  void generateChildren();
};

}  // namespace solver

#endif  // FG_SOLVER_NODE_H_