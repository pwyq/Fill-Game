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

namespace solver {
namespace pns {

class PNS {
 public:
  explicit PNS(const Game& game);
  short getResult(helper::PLAYER root_player = helper::PLAYER::BLACK);

  helper::Move best_move() const;

 protected:
  Node* root_;
  helper::Move best_move_;  // used for selecting next move when playing against Human/Other AI

  short solve(Node* root, helper::PLAYER player);
  Node* selectMostProvingNode(Node* node);
  void expandNode(Node* node);
  Node* updateAncestors(Node* node, Node* root);
  void generateChildren(Node* node);
};

}  // namespace pns
}  // namespace solver

#endif  // FG_SOLVER_PNS_H_