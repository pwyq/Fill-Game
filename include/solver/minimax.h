/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-15 13:57:46
 * @modify date 2023-03-18 00:52:19
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
  explicit Minimax(const Game& game);
  short solve(Node& node, uint16_t depth, helper::PLAYER player);
  short solveAlphaBeta(Node& node, uint16_t depth, short alpha, short beta, helper::PLAYER player);
  short getResult();
  short getAlphaBetaResult();
  uint16_t countEmptyCells(Node& node);
};

}  // namespace minimax
}  // namespace solver

#endif  // FG_SOLVER_MINIMAX_H_