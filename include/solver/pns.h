/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 17:03:28
 * @modify date 2023-03-21 17:59:52
 * @desc Proof Number Search
 */
#ifndef FG_SOLVER_PNS_H_
#define FG_SOLVER_PNS_H_

#include "pns_node.h"

namespace solver::pns {

class PNS {
 public:
  explicit PNS(const Game& game);
  short getResult(helper::PLAYER root_player = helper::PLAYER::BLACK);

  helper::Move bestMove() const;

  size_t getNodeCount() const {
    return node_count_;
  };

 protected:
  Node* root_;
  helper::Move best_move_;  // used for selecting next move when playing against Human/Other AI
  size_t node_count_;

  short solve(Node* root, helper::PLAYER player);
  Node* selectMostProvingNode(Node* node);
  void expandNode(Node* node);
  Node* updateAncestors(Node* node, Node* root);
  void generateChildren(Node* node);
};

}  // namespace solver::pns

#endif  // FG_SOLVER_PNS_H_
