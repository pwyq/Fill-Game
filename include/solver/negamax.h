/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 11:14:21
 * @modify date 2023-04-03 19:48:17
 * @desc Negamax
 */

#ifndef FG_SOLVER_NEGAMAX_H_
#define FG_SOLVER_NEGAMAX_H_
// std
#include <iostream>

//local
#include "game.h"
#include "helper.h"
#include "node.h"

using std::cerr;
using std::endl;

namespace solver::negamax {

// This TT setup is only for alpha-beta
enum EntryFlag {
  EXACT   = 0,
  L_BOUND = 1,
  U_BOUND = 2
};

struct ttEntry {
  bool is_valid  = false;
  uint16_t depth = 0;
  uint8_t flag   = 0;
  short value    = 0;
};

class Negamax {
 public:
  explicit Negamax(const Game& game);
  short getResult();
  short getAlphaBetaResult();
  short getAlphaBetaTranspositionTableResult();

  helper::Move bestMove() const;

 private:
  Node root_;
  std::unordered_map<std::string, ttEntry> tt_;
  helper::Move best_move_;  // used for selecting next move when playing against Human/Other AI

  ttEntry transpositionTableLookup(NodeTT& node);
  inline void transpositionTableStore(NodeTT& node, ttEntry entry);

  short solve(Node& node, uint16_t depth, helper::PLAYER player);
  short solveAlphaBeta(Node& node, uint16_t depth, short alpha, short beta, helper::PLAYER player);
  short solveAlphaBetaTranspositionTable(NodeTT& node, uint16_t depth, short alpha, short beta, helper::PLAYER player);
  uint16_t countEmptyCells(Node& node);
};

inline void Negamax::transpositionTableStore(NodeTT& node, ttEntry entry) {
  entry.is_valid = true;
  tt_[node.id()] = entry;
}

}  // namespace solver::negamax

#endif  // FG_SOLVER_NEGAMAX_H_
