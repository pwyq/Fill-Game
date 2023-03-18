/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-15 13:57:51
 * @modify date 2023-03-17 15:52:05
 */
#include "solver/minimax.h"
// std
#include <iostream>

namespace solver {
namespace minimax {

Minimax::Minimax(const Game& game) : root_(game) {
  // if given a already end-game board
  if (root_.game_.isTerminal()) {
    std::cerr << "result of minimax is " << -1 << std::endl;
    return;
  }
}

int Minimax::getResult() {
  return solve(root_, countEmptyCells(root_), helper::PLAYER::BLACK);
}

int Minimax::solve(Node& node, uint16_t depth, helper::PLAYER player) {
  node.evaluate(player);
  if (depth == 0 || node.game_.isTerminal()) {
    return node.eval_val_;
  }
  node.generateChildren(player);

  if (player == helper::PLAYER::BLACK) {
    int max_eval = -INF;
    for (auto& child : node.children_) {
      int eval = solve(child, depth - 1, helper::PLAYER::WHITE);
      max_eval = std::max(max_eval, eval);
    }
    return max_eval;
  } else {
    // if it's minimizing player
    int min_eval = INF;
    for (auto& child : node.children_) {
      int eval = solve(child, depth - 1, helper::PLAYER::BLACK);
      min_eval = std::min(min_eval, eval);
    }
    return min_eval;
  }
}

/**
 * @brief count the number of empty cells in the root node
 *        The return is used for the starting `depth`
 * 
 *        TODO: optimum depth for minimax?
 * @param node 
 * @return uint16_t 
 */
uint16_t Minimax::countEmptyCells(Node& node) {
  uint16_t res = 0;
  for (auto& c : node.game_.toString()) {
    if (c == '.') {
      res += 1;
    }
  }
  return res;
}

}  // namespace minimax
}  // namespace solver
