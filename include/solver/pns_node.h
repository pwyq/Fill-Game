/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-21 17:15:30
 * @modify date 2023-03-21 17:59:32
 * @desc PNS Node
 */

#ifndef FG_SOLVER_PNS_NODE_H_
#define FG_SOLVER_PNS_NODE_H_
// local
#include "game.h"

namespace solver {
namespace pns {

class Node {
 public:
  explicit Node(const Game &game, helper::NODE_TYPE type, Node *parent, helper::PLAYER player);
  Node(const Game &game, const Pos &pos, uint8_t value, helper::NODE_TYPE type, Node *parent, helper::PLAYER player);
  ~Node();

  void evaluate();
  void addChild(Node *node);
  void deleteSubtree();
  void setProofAndDisproofNumbers();
  inline void setExpanded(bool b) { is_expanded_ = b; }

  inline Game game() const { return game_; }
  inline helper::NODE_TYPE type() const { return type_; }
  inline Node *parent() const { return parent_; }
  inline Node *children() const { return children_; }
  inline Node *sibling() const { return sibling_; }
  inline helper::Move move() const { return move_; }
  inline helper::PLAYER player() const { return player_; }
  inline helper::PROOF_VALUE value() const { return value_; }
  inline bool isExpanded() const { return is_expanded_; }
  inline uint32_t pn() const { return pn_; }
  inline uint32_t dn() const { return dn_; }

 private:
  Game game_;
  helper::NODE_TYPE type_ = helper::NODE_TYPE::OR;
  Node *parent_           = nullptr;
  Node *children_         = nullptr;
  Node *sibling_          = nullptr;
  helper::PLAYER player_;
  bool is_expanded_ = false;

  // Note: pn/dn cannot be smaller than uint32_t; otherwise seg fault
  uint32_t pn_ = 1;
  uint32_t dn_ = 1;

  helper::PROOF_VALUE value_ = helper::PROOF_VALUE::UNKNOWN;
  helper::Move move_;
};

}  // namespace pns
}  // namespace solver
#endif