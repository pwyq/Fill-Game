/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-21 17:17:43
 * @modify date 2023-03-21 17:59:51
 */
// local
#include "solver/pns_node.h"

namespace solver {
namespace pns {

Node::Node(const Game &game, helper::NODE_TYPE type, Node *parent, helper::PLAYER player)
    : game_(game), type_(type), parent_(parent), player_(player) {
}

Node::Node(const Game &game, const Pos &pos, uint8_t value, helper::NODE_TYPE type, Node *parent, helper::PLAYER player)
    : game_(game), type_(type), parent_(parent), player_(player) {
  move_ = {pos, value};
  game_.unsafePlay(pos, value);
}

Node::~Node() {
  deleteSubtree();
}

void Node::addChild(Node *node) {
  if (children_ == nullptr) {
    children_ = node;
  } else {
    Node *tmp = children_;
    while (tmp->sibling_ != nullptr) {
      tmp = tmp->sibling_;
    }
    tmp->sibling_ = node;
  }
}

void Node::deleteSubtree() {
  Node *elem = children_;
  while (children_ != nullptr) {
    elem      = children_;
    children_ = children_->sibling_;
    delete elem;
  }
}

void Node::evaluate() {
  if (game_.isTerminal()) {
    value_ = (helper::NODE_TYPE::OR == type_) ? helper::PROOF_VALUE::LOSS : helper::PROOF_VALUE::WIN;
  } else {
    value_ = helper::PROOF_VALUE::UNKNOWN;
  }
}

/**
 * @brief Set PN and DN of a PNS node. It was in the PNS class, and was moved here for scope concerns.
 * 
 */
void Node::setProofAndDisproofNumbers() {
  if (is_expanded_) {
    if (type_ == helper::NODE_TYPE::AND) {
      pn_ = 0;
      dn_ = INF;

      Node *n = children_;
      while (n != nullptr) {
        pn_ += n->pn_;
        if (n->dn_ < dn_) {
          dn_ = n->dn_;
        }
        n = n->sibling_;
      }
    } else {
      pn_ = INF;
      dn_ = 0;

      Node *n = children_;
      while (n != nullptr) {
        dn_ += n->dn_;
        if (n->pn_ < pn_) {
          pn_ = n->pn_;
        }
        n = n->sibling_;
      }
    }
  } else {
    switch (value_) {
      case helper::PROOF_VALUE::WIN:
        pn_ = 0;
        dn_ = INF;
        break;
      case helper::PROOF_VALUE::LOSS:
        pn_ = INF;
        dn_ = 0;
        break;
      case helper::PROOF_VALUE::UNKNOWN:
        pn_ = 1;
        dn_ = 1;
        break;
    }
  }
}

}  // namespace pns
}  // namespace solver