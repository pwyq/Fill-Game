/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-15 13:57:46
 * @modify date 2023-04-05 23:32:46
 * @desc Minimax implementation
 */

#ifndef FG_SOLVER_MINIMAX_H_
#define FG_SOLVER_MINIMAX_H_
// local
#include "game.h"
#include "helper.h"
#include "node.h"

namespace solver::minimax {

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

class Minimax {
 public:
  explicit Minimax(const Game& game);
  short getResult();
  short getAlphaBetaResult();
  short getAlphaBetaTranspositionTableResult();

  helper::Move bestMove() const;

  size_t getNodeCount() {
    return node_count_;
  };

 private:
  Node root_;
  std::unordered_map<std::string, ttEntry> tt_;
  helper::Move best_move_;                    // used for selecting next move when playing against Human/Other AI
  std::vector<helper::Move> possible_moves_;  // for random selection

  ttEntry transpositionTableLookup(NodeTT& node);
  inline void transpositionTableStore(NodeTT& node, ttEntry entry);

  short solve(Node& node, uint16_t depth, helper::PLAYER player);
  short solveAlphaBeta(Node& node, uint16_t depth, short alpha, short beta, helper::PLAYER player);
  short solveAlphaBetaTranspositionTable(NodeTT& node, uint16_t depth, short alpha, short beta, helper::PLAYER player);
  uint16_t countEmptyCells(Node& node);

  size_t node_count_;
};

inline void Minimax::transpositionTableStore(NodeTT& node, ttEntry entry) {
  entry.is_valid = true;
  tt_[node.id()] = entry;
}

}  // namespace solver::minimax

#endif  // FG_SOLVER_MINIMAX_H_
