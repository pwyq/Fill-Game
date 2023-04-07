/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-15 13:57:51
 * @modify date 2023-04-05 23:32:49
 * 
 * TODO: is there a better way to get the best_move? 
 *    We are now returning the immediate win move if found one; otherwise return random.
 *    This is done by iterating the child, which can be inefficient.
 *    ALTERNATIVE is to keep track of a move sequense, from depth=1 child all the way to the result (linked list? memory would be an issue)
 */
#include "solver/minimax.h"
// std
#include <iostream>

namespace solver {
namespace minimax {

Minimax::Minimax(const Game& game) : root_(game) {
  best_move_      = helper::Move{Pos{0, 0}, 0};
  possible_moves_ = {};
}

short Minimax::getResult() {
  if (root_.game().isTerminal()) {
    return -1;
  }

  // Finding the best move
  //  iterating through the depth=1 children, if we found an immediate win with the child, then return that move
  //  This only works for plain minimax
  root_.evaluate(helper::PLAYER::BLACK);
  root_.generateChildren();
  uint16_t depth = countEmptyCells(root_) - 1;
  for (auto& child : root_.children()) {
    short res = solve(child, depth, helper::PLAYER::WHITE);
    if (res == 1) {
      best_move_ = child.move();
      return 1;
    } else {
      possible_moves_.push_back(child.move());
    }
  }
  return -1;
  // return solve(root_, depth, helper::PLAYER::BLACK);
}

short Minimax::getAlphaBetaResult() {
  if (root_.game().isTerminal()) {
    return -1;
  }

  // Finding the best move
  //  iterating through the depth=1 children, if we found an immediate win with the child, then return that move
  //  Note that we must run from the root node first; otherwise, the children ttEntry will be polluted.
  uint16_t depth  = countEmptyCells(root_);
  short final_res = solveAlphaBeta(root_, depth, -INF_SHORT, +INF_SHORT, helper::PLAYER::BLACK);

  for (auto& child : root_.children()) {
    short res = solveAlphaBeta(child, depth, -INF_SHORT, +INF_SHORT, helper::PLAYER::WHITE);
    if (res == 1) {
      best_move_ = child.move();
      break;
    } else {
      possible_moves_.push_back(child.move());
    }
  }
  return final_res;
  // return solveAlphaBeta(root_, countEmptyCells(root_), -INF_SHORT, +INF_SHORT, helper::PLAYER::BLACK);
}

short Minimax::getAlphaBetaTranspositionTableResult() {
  if (root_.game().isTerminal()) {
    return -1;
  }
  NodeTT rootTT_(root_.game());
  uint16_t depth = countEmptyCells(root_);

  short final_res = solveAlphaBetaTranspositionTable(rootTT_, depth, -INF_SHORT, +INF_SHORT, helper::PLAYER::BLACK);

  for (auto& child : rootTT_.children()) {
    short res = solveAlphaBetaTranspositionTable(child, depth, -INF_SHORT, +INF_SHORT, helper::PLAYER::WHITE);
    if (res == 1) {
      best_move_ = child.move();
      break;
    } else {
      possible_moves_.push_back(child.move());
    }
  }
  return final_res;
  // return solveAlphaBetaTranspositionTable(rootTT_, countEmptyCells(root_), -INF_SHORT, +INF_SHORT, helper::PLAYER::BLACK);
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
    return max_eval;
  } else {
    // if it's minimizing player
    short min_eval = INF_SHORT;
    for (auto& child : node.children()) {
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
  node.generateChildren();

  short best_eval = (player == helper::PLAYER::BLACK) ? -INF_SHORT : INF_SHORT;
  if (player == helper::PLAYER::BLACK) {
    for (auto& child : node.children()) {
      short eval = solveAlphaBetaTranspositionTable(child, depth - 1, alpha, beta, helper::PLAYER::WHITE);
      best_eval  = std::max(best_eval, eval);

      alpha = std::max(alpha, eval);
      if (beta <= alpha) {
        break;
      }
    }
  } else {
    // if it's minimizing player
    for (auto& child : node.children()) {
      short eval = solveAlphaBetaTranspositionTable(child, depth - 1, alpha, beta, helper::PLAYER::BLACK);
      best_eval  = std::min(best_eval, eval);

      beta = std::min(beta, eval);
      if (beta <= alpha) {
        break;
      }
    }
  }

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

/**
 * @brief Return the first move that result in a WIN
 *        if not found
 *          no time limit, resign (return a dummy value) {{0,0}, 0}
 *          has time limit, return a random move (todo? that hasn't been examined)
 *
 * @return helper::Move
 */
helper::Move Minimax::bestMove() const {
  // if game is terminal
  // 	return 0
  // if move != 0
  // 	return move
  // if move == 0 and game is not terminal
  // 	return random

  if (root_.game().isTerminal() || best_move_.value != 0) {
    return best_move_;
  }

  // if has time limit (the agent is probably forced to stop) return a random move
  auto move = possible_moves_[rand() % possible_moves_.size() + 1];
  return move;
}

}  // namespace minimax
}  // namespace solver
