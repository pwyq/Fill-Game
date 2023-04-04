/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-15 13:57:51
 * @modify date 2023-03-21 17:59:47
 */
#include "solver/minimax.h"
// std
#include <iostream>

namespace solver {
namespace minimax {

Minimax::Minimax(const Game& game) : root_(game) {
}

short Minimax::getResult(helper::PLAYER root_player) {
  if (root_.game().isTerminal()) {
    return -1;
  }
  return solve(root_, countEmptyCells(root_), root_player);
}

short Minimax::getAlphaBetaResult(helper::PLAYER root_player) {
  if (root_.game().isTerminal()) {
    return -1;
  }
  return solveAlphaBeta(root_, countEmptyCells(root_), -INF_SHORT, +INF_SHORT, root_player);
}

short Minimax::getAlphaBetaTranspositionTableResult(helper::PLAYER root_player) {
  if (root_.game().isTerminal()) {
    return -1;
  }
  NodeTT rootTT_(root_.game());
  return solveAlphaBetaTranspositionTable(rootTT_, countEmptyCells(root_), -INF_SHORT, +INF_SHORT, root_player);
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
  if (depth == 0 || node.game().isTerminal()) {
    return node.value();
  }
  node.generateChildren();

  if (player == helper::PLAYER::BLACK) {
    short max_eval = -INF_SHORT;
    for (auto& child : node.children()) {
      short eval = solve(child, depth - 1, helper::PLAYER::WHITE);
      max_eval   = std::max(max_eval, eval);
    }
    // node.deleteChildren();
    return max_eval;
  } else {
    // if it's minimizing player
    short min_eval = INF_SHORT;
    for (auto& child : node.children()) {
      short eval = solve(child, depth - 1, helper::PLAYER::BLACK);
      min_eval   = std::min(min_eval, eval);
    }
    // node.deleteChildren();
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
  if (depth == 0 || node.game().isTerminal()) {
    return node.value();
  }
  node.generateChildren();

  if (player == helper::PLAYER::BLACK) {
    short max_eval = -INF_SHORT;
    for (auto& child : node.children()) {
      short eval = solveAlphaBeta(child, depth - 1, alpha, beta, helper::PLAYER::WHITE);
      max_eval   = std::max(max_eval, eval);

      alpha = std::max(alpha, eval);
      if (beta <= alpha) {
        break;
      }
    }
    node.deleteChildren();
    return max_eval;
  } else {
    // if it's minimizing player
    short min_eval = INF_SHORT;
    for (auto& child : node.children()) {
      short eval = solveAlphaBeta(child, depth - 1, alpha, beta, helper::PLAYER::BLACK);
      min_eval   = std::min(min_eval, eval);

      beta = std::min(beta, eval);
      if (beta <= alpha) {
        break;
      }
    }
    node.deleteChildren();
    return min_eval;
  }
}

/**
 * @brief This is the Minimax with alpha-beta pruning + transposition table
 *
 * @param node
 * @param depth
 * @param alpha
 * @param beta
 * @param player
 * @return short  1 for WIN, -1 for LOSS
 */
short Minimax::solveAlphaBetaTranspositionTable(NodeTT& node, uint16_t depth, short alpha, short beta, helper::PLAYER player) {
  short old_alpha = alpha;

  // get tt entry
  ttEntry entry = transpositionTableLookup(node);
  if (true == entry.is_valid && entry.depth >= depth) {
    switch (entry.flag) {
      case EntryFlag::EXACT:
        return entry.value;
      case EntryFlag::L_BOUND:
        alpha = std::max(alpha, entry.value);
        break;
      case EntryFlag::U_BOUND:
        beta = std::min(beta, entry.value);
        break;
      default:
        break;
    }
    if (alpha >= beta) {
      return entry.value;
    }
  }

  node.evaluate(player);
  if (depth == 0 || node.game().isTerminal()) {
    return node.value();
  }
  // node.generateChildren();

  short best_eval = (player == helper::PLAYER::BLACK) ? -INF_SHORT : INF_SHORT;
  if (player == helper::PLAYER::BLACK) {
    for (auto& child : node.children()) {
      short eval = solveAlphaBeta(child, depth - 1, alpha, beta, helper::PLAYER::WHITE);
      best_eval  = std::max(best_eval, eval);

      alpha = std::max(alpha, eval);
      if (beta <= alpha) {
        break;
      }
    }
  } else {
    // if it's minimizing player
    for (auto& child : node.children()) {
      short eval = solveAlphaBeta(child, depth - 1, alpha, beta, helper::PLAYER::BLACK);
      best_eval  = std::min(best_eval, eval);

      beta = std::min(beta, eval);
      if (beta <= alpha) {
        break;
      }
    }
  }

  node.deleteChildren();

  // store tt entry
  entry.value = best_eval;
  if (best_eval <= old_alpha) {
    entry.flag = EntryFlag::U_BOUND;
  } else if (best_eval >= beta) {
    entry.flag = EntryFlag::L_BOUND;
  } else {
    entry.flag = EntryFlag::EXACT;
  }
  entry.depth = depth;
  transpositionTableStore(node, entry);

  return best_eval;
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
  for (auto& c : node.game().toString()) {
    if (c == '.') {
      res += 1;
    }
  }
  return res;
}

ttEntry Minimax::transpositionTableLookup(NodeTT& node) {
  if (tt_.find(node.id()) != tt_.end()) {
    return tt_[node.id()];
  } else {
    ttEntry temp;
    return temp;
  }
}

}  // namespace minimax
}  // namespace solver
