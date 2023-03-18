/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-15 13:57:46
 * @modify date 2023-03-15 15:57:14
 * @desc Minimax implementation
 */

#ifndef FG_SOLVER_MINIMAX_H_
#define FG_SOLVER_MINIMAX_H_
//local
#include "game.h"
#include "helper.h"
#include "node.h"

namespace solver {
namespace minimax {

class Minimax {
 public:
  Node root_;
  helper::Move best_move_;  // used for selecting next move when playing against Human/Other AI
  explicit Minimax(const Game& game);
  int solve(Node& node, uint16_t depth, helper::PLAYER player);
  int getResult();
  uint16_t countEmptyCells(Node& node);
};

}  // namespace minimax
}  // namespace solver

#endif  // FG_SOLVER_MINIMAX_H_