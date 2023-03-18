/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 11:14:21
 * @modify date 2023-03-18 11:14:21
 * @desc Negamax
 */

#ifndef FG_SOLVER_NEGAMAX_H_
#define FG_SOLVER_NEGAMAX_H_
//local
#include "game.h"
#include "helper.h"
#include "node.h"

namespace solver {
namespace negamax {

class Negamax {
 public:
  Node root_;
  explicit Negamax(const Game& game);
  short solve(Node& node, uint16_t depth, helper::PLAYER player);
  short solveAlphaBeta(Node& node, uint16_t depth, short alpha, short beta, helper::PLAYER player);
  short getResult();
  short getAlphaBetaResult();
  uint16_t countEmptyCells(Node& node);
  helper::PLAYER swapPlayer(helper::PLAYER curr_player);
};

}  // namespace negamax
}  // namespace solver

#endif  // FG_SOLVER_MINIMAX_H_