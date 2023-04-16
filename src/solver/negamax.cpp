/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 11:18:44
 * @modify date 2023-04-05 23:32:38
 */

#include "solver/negamax.h"

namespace solver {
namespace negamax {

Negamax::Negamax(const Game& game) : root_(game), tt_({}) {
  best_move_      = helper::Move{Pos{0, 0}, 0};
  possible_moves_ = {};
  node_count_     = 0;
}

short Negamax::getResult() {
  if (root_.game().isTerminal()) {
    return -1;
  }

  node_count_ = 0;

  // Finding the best move
  //  iterating through the depth=1 children, if we found an immediate win with the child, then return that move
  //  Note that we must run from the root node first; otherwise, the children ttEntry will be polluted.
  uint16_t depth  = countEmptyCells(root_);
  short final_res = solve(root_, depth, helper::PLAYER::BLACK);

  node_count_ = 1;

  for (auto& child : root_.children()) {
    short res = solve(child, depth, helper::PLAYER::WHITE);
    if (res == -1) {  // note here differs from minimax
      best_move_ = child.move();
      break;
    } else {
      possible_moves_.push_back(child.move());
    }
  }
  return final_res;
  // return solve(root_, countEmptyCells(root_), helper::PLAYER::BLACK);
}

short Negamax::getAlphaBetaResult() {
  if (root_.game().isTerminal()) {
    return -1;
  }

  node_count_ = 0;

  // Finding the best move
  //  iterating through the depth=1 children, if we found an immediate win with the child, then return that move
  //  Note that we must run from the root node first; otherwise, the children ttEntry will be polluted.
  uint16_t depth  = countEmptyCells(root_);
  short final_res = solveAlphaBeta(root_, depth, -INF_SHORT, +INF_SHORT, helper::PLAYER::BLACK);

  node_count_ = 1;

  for (auto& child : root_.children()) {
    short res = solveAlphaBeta(child, depth, -INF_SHORT, +INF_SHORT, helper::PLAYER::WHITE);
    if (res == -1) {  // note here differs from minimax
      best_move_ = child.move();
      break;
    } else {
      possible_moves_.push_back(child.move());
    }
  }
  return final_res;
  // return solveAlphaBeta(root_, countEmptyCells(root_), -INF_SHORT, +INF_SHORT, helper::PLAYER::BLACK);
}

short Negamax::getAlphaBetaTranspositionTableResult() {
  if (root_.game().isTerminal()) {
    return -1;
  }
  NodeTT rootTT_(root_.game());

  node_count_ = 0;

  // Finding the best move
  //  iterating through the depth=1 children, if we found an immediate win with the child, then return that move
  //  Note that we must run from the root node first; otherwise, the children ttEntry will be polluted.
  uint16_t depth  = countEmptyCells(root_);
  short final_res = solveAlphaBetaTranspositionTable(rootTT_, depth, -INF_SHORT, +INF_SHORT, helper::PLAYER::BLACK);

  node_count_ = 1;

  for (auto& child : rootTT_.children()) {
    short res = solveAlphaBetaTranspositionTable(child, depth, -INF_SHORT, +INF_SHORT, helper::PLAYER::WHITE);
    if (res == -1) {  // note here differs from minimax
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
 * @brief This is the plain Negamax algorithm
 *
 * @param node
 * @param depth
 * @param player
 * @return short  1 for WIN, -1 for LOSS
 */
short Negamax::solve(Node& node, uint16_t depth, helper::PLAYER player) {
  ++node_count_;

  if (depth == 0 || node.game().isTerminal()) {
    return -1;
  }
  node.generateChildren();

  short best_eval = -INF_SHORT;
  for (auto& child : node.children()) {
    short eval = -solve(child, depth - 1, helper::changePlayer(player));
    best_eval  = std::max(best_eval, eval);
  }
  return best_eval;
}

/**
 * @brief This is the Negamax with alpha-beta pruning
 *
 * @param node
 * @param depth
 * @param alpha
 * @param beta
 * @param player
 * @return short  1 for WIN, -1 for LOSS
 */
short Negamax::solveAlphaBeta(Node& node, uint16_t depth, short alpha, short beta, helper::PLAYER player) {
  ++node_count_;

  if (depth == 0 || node.game().isTerminal()) {
    if (best_move_.value == 0 && player == helper::WHITE) {
      best_move_ = node.move();
    }
    return -1;
  }
  node.generateChildren();

  short best_eval = -INF_SHORT;
  for (auto& child : node.children()) {
    short eval = -solveAlphaBeta(child, depth - 1, -beta, -alpha, helper::changePlayer(player));
    best_eval  = std::max(best_eval, eval);

    alpha = std::max(alpha, eval);
    if (alpha >= beta) {
      break;
    }
  }
  return best_eval;
}

/**
 * @brief This is the Negamax with alpha-beta pruning + transposition table
 *        https://en.wikipedia.org/wiki/Negamax#Negamax_with_alpha_beta_pruning_and_transposition_tables
 *
 * @param node
 * @param depth
 * @param alpha
 * @param beta
 * @param player
 * @return short  1 for WIN, -1 for LOSS
 */
short Negamax::solveAlphaBetaTranspositionTable(NodeTT& node, uint16_t depth, short alpha, short beta, helper::PLAYER player) {
  short old_alpha = alpha;

  ++node_count_;

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

  if (depth == 0 || node.game().isTerminal()) {
    if (best_move_.value == 0 && player == helper::WHITE) {
      best_move_ = node.move();
    }
    return -1;
  }
  node.generateChildren();

  short best_eval = -INF_SHORT;
  for (auto& child : node.children()) {
    short eval = -solveAlphaBetaTranspositionTable(child, depth - 1, -beta, -alpha, helper::changePlayer(player));
    best_eval  = std::max(best_eval, eval);

    alpha = std::max(alpha, eval);
    if (alpha >= beta) {
      break;
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
uint16_t Negamax::countEmptyCells(Node& node) {
  uint16_t res = 0;
  for (auto& c : node.game().toString()) {
    if (c == '.') {
      res += 1;
    }
  }
  return res;
}

ttEntry Negamax::transpositionTableLookup(NodeTT& node) {
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
helper::Move Negamax::bestMove() const {
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

}  // namespace negamax
}  // namespace solver
