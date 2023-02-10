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

namespace Solver {

class Node {
 public:
  explicit Node(const Game &game);

  Node(const Game &game, const Pos &pos, uint8_t value);

  Game game;
  uint32_t phi;
  uint32_t delta;
  bool is_expanded;

  Move move;
  std::string id;

  std::vector<Node> children{};

  void evaluate();

  void generateChildren();
};

}  // namespace Solver

#endif  // FG_SOLVER_NODE_H_