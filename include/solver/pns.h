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
  Node root_;

  explicit PNS(const Game& game);
  short getResult(helper::PLAYER root_player = helper::PLAYER::BLACK);

 protected:
  short solve(helper::PLAYER root_player = helper::PLAYER::BLACK);
  void setProofAndDisproofNumbers(Node* node);
  Node* selectMostProvingNode(Node* node);
  void expandNode(Node* node, helper::PLAYER root_player);
  Node* updateAncestors(Node* node);
};

class PNS2 {
 public:
  Node2* root_;
  explicit PNS2(const Game& game);
  short getResult();
  short solveGame(Node2* root);
  helper::PLAYER changePlayer(helper::PLAYER player);
  void setProofAndDisproofNumbers(Node2* node);
  Node2* selectMostProvingNode(Node2* node);
  void expandNode(Node2* node);
  Node2* updateAncestors(Node2* node, Node2* root);
  void generateChildren(Node2* node);
};

}  // namespace pns
}  // namespace solver

#endif  // FG_SOLVER_PNS_H_