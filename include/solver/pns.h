/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 17:03:28
 * @modify date 2023-03-19 11:47:32
 * @desc Proof Number Search
 */
#ifndef FG_SOLVER_PNS_H_
#define FG_SOLVER_PNS_H_

#include "node.h"

namespace solver {
namespace pns {

class PNS {
 public:
  explicit PNS(const Game& game);
  short getResult();

 protected:
  Node* root_;
  short solveGame(Node* root);
  helper::PLAYER changePlayer(helper::PLAYER player);
  void setProofAndDisproofNumbers(Node* node);
  Node* selectMostProvingNode(Node* node);
  void expandNode(Node* node);
  Node* updateAncestors(Node* node, Node* root);
  void generateChildren(Node* node);
};

}  // namespace pns
}  // namespace solver

#endif  // FG_SOLVER_PNS_H_