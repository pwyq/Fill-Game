/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-15 13:57:51
 * @modify date 2023-03-18 11:44:07
 */
#include "solver/minimax.h"
// std
#include <iostream>

namespace solver {
namespace minimax {

Minimax::Minimax(const Game& game) : root_(game) {
}

short Minimax::getResult(helper::PLAYER root_player) {
  if (root_.game_.isTerminal()) {
    return -1;
  }
  return solve(root_, countEmptyCells(root_), root_player);
}

short Minimax::getAlphaBetaResult(helper::PLAYER root_player) {
  if (root_.game_.isTerminal()) {
    return -1;
  }
  return solveAlphaBeta(root_, countEmptyCells(root_), -INF_SHORT, +INF_SHORT, root_player);
}

/**
 * @brief This is the plain Minimax algorithm
 * 
 * @param node 
 * @param depth 
 * @param player 
 * @return short  1 for WIN, -1 for LOSS
 */
short Minimax::solve(Node& node, uint16_t depth, helper::PLAYER player) {
  node.evaluate(player);
  if (depth == 0 || node.game_.isTerminal()) {
    return node.eval_val_;
  }
  node.generateChildren();

  if (player == helper::PLAYER::BLACK) {
    short max_eval = -INF_SHORT;
    for (auto& child : node.children_) {
      short eval = solve(child, depth - 1, helper::PLAYER::WHITE);
      max_eval   = std::max(max_eval, eval);
    }
    return max_eval;
  } else {
    // if it's minimizing player
    short min_eval = INF_SHORT;
    for (auto& child : node.children_) {
      short eval = solve(child, depth - 1, helper::PLAYER::BLACK);
      min_eval   = std::min(min_eval, eval);
    }
    return min_eval;
  }
}

/**
 * @brief This is the Minimax with alpha-beta pruning
 * 
 * @param node 
 * @param depth 
 * @param alpha 
 * @param beta 
 * @param player 
 * @return short  1 for WIN, -1 for LOSS
 */
short Minimax::solveAlphaBeta(Node& node, uint16_t depth, short alpha, short beta, helper::PLAYER player) {
  node.evaluate(player);
  if (depth == 0 || node.game_.isTerminal()) {
    return node.eval_val_;
  }
  node.generateChildren();

  if (player == helper::PLAYER::BLACK) {
    short max_eval = -INF_SHORT;
    for (auto& child : node.children_) {
      short eval = solveAlphaBeta(child, depth - 1, alpha, beta, helper::PLAYER::WHITE);
      max_eval   = std::max(max_eval, eval);

      alpha = std::max(alpha, eval);
      if (beta <= alpha) {
        break;
      }
    }
    return max_eval;
  } else {
    // if it's minimizing player
    short min_eval = INF_SHORT;
    for (auto& child : node.children_) {
      short eval = solveAlphaBeta(child, depth - 1, alpha, beta, helper::PLAYER::BLACK);
      min_eval   = std::min(min_eval, eval);

      beta = std::min(beta, eval);
      if (beta <= alpha) {
        break;
      }
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
