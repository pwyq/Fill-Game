/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 11:18:44
 * @modify date 2023-03-18 11:43:59
 */

#include "solver/negamax.h"
// std
#include <iostream>

namespace solver {
namespace negamax {

Negamax::Negamax(const Game& game) : root_(game) {
}

short Negamax::getResult() {
  if (root_.game_.isTerminal()) {
    return -1;
  }
  return solve(root_, countEmptyCells(root_), helper::PLAYER::BLACK);
}

short Negamax::getAlphaBetaResult() {
  if (root_.game_.isTerminal()) {
    return -1;
  }
  return solveAlphaBeta(root_, countEmptyCells(root_), -INF_SHORT, +INF_SHORT, helper::PLAYER::BLACK);
}

/**
 * @brief This is the plain Negamax algorithm
 * 
 * @param node 
 * @param player 
 * @return short  1 for WIN, -1 for LOSS
 */
short Negamax::solve(Node& node, uint16_t depth, helper::PLAYER player) {
  if (depth == 0 || node.game_.isTerminal()) {
    return -1;
  }
  node.generateChildren(player);

  short best_eval = -INF_SHORT;
  for (auto& child : node.children_) {
    short eval = -solve(child, depth - 1, swapPlayer(player));
    best_eval  = std::max(best_eval, eval);
  }
  return best_eval;
}

/**
 * @brief This is the Negamax with alpha-beta pruning
 * 
 * @param node 
 * @param alpha 
 * @param beta 
 * @param player 
 * @return short  1 for WIN, -1 for LOSS
 */
short Negamax::solveAlphaBeta(Node& node, uint16_t depth, short alpha, short beta, helper::PLAYER player) {
  return -2;
}

/**
 * @brief count the number of empty cells in the root node
 *        The return is used for the starting `depth`
 * 
 *        TODO: optimum depth for minimax?
 * @param node 
 * @return uint16_t 
 */
uint16_t Negamax::countEmptyCells(Node& node) {
  uint16_t res = 0;
  for (auto& c : node.game_.toString()) {
    if (c == '.') {
      res += 1;
    }
  }
  return res;
}

helper::PLAYER Negamax::swapPlayer(helper::PLAYER curr_player) {
  return (curr_player == helper::PLAYER::WHITE) ? helper::PLAYER::BLACK : helper::PLAYER::WHITE;
}

}  // namespace negamax
}  // namespace solver
