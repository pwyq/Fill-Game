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
  root_.eval_val_ = 0;

  // initial call
  int res = solve(root_, 10, helper::PLAYER::BLACK);
  std::cerr << "result of minimax is " << res << std::endl;
}

int Minimax::solve(Node& node, int depth, helper::PLAYER player) {
  std::cerr << "\n--------------------------" << std::endl;
  std::cerr << "depth = " << depth << ", player = " << player << std::endl;
  std::cerr << "game = " << node.game_.toString() << std::endl;
  std::cerr << "node eval = " << node.eval_val_ << std::endl;
  if (depth == 0 || node.game_.isTerminal()) {
    std::cerr << "Reaching terminal..." << std::endl;
    return node.eval_val_;
  }
  node.generateChildren();

  if (player == helper::PLAYER::BLACK) {
    // if it's maximizing player
    int max_eval = -INF;
    for (auto& child : node.children_) {
      std::cerr << "child game = " << child.game_.toString() << std::endl;
      int eval = solve(child, depth - 1, helper::PLAYER::WHITE);
      std::cerr << "child eval = " << eval << std::endl;
      max_eval = std::max(max_eval, eval);
    }
    return max_eval;
  } else {
    // if it's minimizing player
    int min_eval = INF;
    for (auto& child : node.children_) {
      std::cerr << "child game = " << child.game_.toString() << std::endl;
      int eval = solve(child, depth - 1, helper::PLAYER::BLACK);
      std::cerr << "child eval = " << eval << std::endl;
      min_eval = std::min(min_eval, eval);
    }
    return min_eval;
  }
}

}  // namespace minimax
}  // namespace solver
