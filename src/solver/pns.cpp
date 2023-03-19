/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 17:05:59
 * @modify date 2023-03-18 22:14:59
 */

#include "solver/pns.h"
// std
#include <iostream>
// local
#include "solver/game.h"
#include "solver/node.h"

namespace solver {
namespace pns {

PNS::PNS(const Game& game) : root_(game) {}

short PNS::getResult(helper::PLAYER root_player) {
  root_.type_ = root_player;
  return solve(root_player);
}

short PNS::solve(helper::PLAYER root_player) {
  root_.evaluate(root_player);
  setProofAndDisproofNumbers(root_);

  Node current = root_;

  while (root_.pn_ != 0 && root_.dn_ != 0) {
    std::cerr << "root.pn = " << root_.pn_ << ", root.dn = " << root_.dn_ << std::endl;
    Node most_proving_node = selectMostProvingNode(current);
    most_proving_node.generateChildren();
    current = updateAncestors(most_proving_node, root_);
  }

  if (root_.pn_ == 0) {
    return 1;
  } else if (root_.dn_ == 0) {
    return -1;
  } else {
    return 0;
  }
}

void PNS::setProofAndDisproofNumbers(Node& node) {
  if (node.is_expanded_) {
    // internal nodes

    if (node.type_ == helper::PLAYER::BLACK) {  // AND type
      node.pn_ = 0;
      node.dn_ = INF;
      for (auto& child : node.children_) {
        node.pn_ += child.pn_;
        if (child.dn_ < node.dn_) {
          node.dn_ = child.dn_;
        }
      }
    } else {  // OR type
      node.pn_ = INF;
      node.dn_ = 0;
      for (auto& child : node.children_) {
        node.dn_ += child.dn_;
        if (child.pn_ < node.pn_) {
          node.pn_ = child.pn_;
        }
      }
    }
  } else {
    // terminal / non-terminal leaf
    switch (node.value_) {
      case helper::PROOF_VALUE::WIN:  // PROVEN
        node.pn_ = 0;
        node.dn_ = INF;
        break;
      case helper::PROOF_VALUE::LOSS:  // DISPROVEN
        node.pn_ = INF;
        node.dn_ = 0;
        break;
      case helper::PROOF_VALUE::UNKNOWN:
        node.pn_ = 1;
        node.dn_ = 1;
        break;
      default:
        break;
    }
  }
}

Node PNS::selectMostProvingNode(Node& node) {
  Node res = node;
  while (node.is_expanded_) {
    uint16_t value = INF;
    if (node.type_ == helper::PLAYER::WHITE) {  // OR type
      for (auto& child : node.children_) {
        if (value > child.pn_) {
          value = child.pn_;
          res   = child;
        }
      }
    } else {  // AND type
      for (auto& child : node.children_) {
        if (value > child.pn_) {
          value = child.pn_;
          res   = child;
        }
      }
    }
    node = res;
  }
  return res;
}

Node PNS::updateAncestors(Node& node, Node& root) {
  while (true) {
    uint16_t old_pn = node.pn_;
    uint16_t old_dn = node.dn_;

    setProofAndDisproofNumbers(node);

    if (old_pn == node.pn_ && old_dn == node.dn_) {
      return node;
    }

    if (node.id_ == root_.id_) {
      return node;
    }

    node = *(node.parent_);
  }
}

}  // namespace pns
}  // namespace solver
