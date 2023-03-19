/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 17:05:59
 * @modify date 2023-03-19 11:47:34
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

  Node& current = root_;

  while (root_.pn_ != 0 && root_.dn_ != 0) {
    std::cerr << "root.pn = " << root_.pn_ << ", root.dn = " << root_.dn_ << std::endl;
    Node& most_proving_node = selectMostProvingNode(current);
    expandNode(most_proving_node, root_player);
    std::cerr << current.game_.toString() << " --> " << most_proving_node.game_.toString() << std::endl;
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
  std::cerr << "setProofAndDisproofNumbers for " << node.game_.toString() << std::endl;
  if (node.is_expanded_) {
    std::cerr << "  node is expanded...\n";
    // internal nodes

    if (node.type_ == helper::PLAYER::BLACK) {  // AND type
      std::cerr << "  node is AND node\n";
      node.pn_ = 0;
      node.dn_ = INF;
      for (auto& child : node.children_) {
        node.pn_ += child.pn_;
        if (child.dn_ < node.dn_) {
          node.dn_ = child.dn_;
        }
      }
    } else {  // OR type
      std::cerr << "  node is OR node\n";

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
    std::cerr << "node value = " << node.value_ << "\n";
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
  std::cerr << "  after setting, node.pn = " << node.pn_ << ", node.dn = " << node.dn_ << "\n\n";
}

Node& PNS::selectMostProvingNode(Node& node) {
  Node* res = &node;
  while (node.is_expanded_) {
    uint16_t value = INF;
    if (node.type_ == helper::PLAYER::WHITE) {  // OR type
      for (auto& child : node.children_) {
        if (value > child.pn_) {
          value = child.pn_;
          res   = &child;
        }
      }
    } else {  // AND type
      for (auto& child : node.children_) {
        if (value > child.pn_) {
          value = child.pn_;
          res   = &child;
        }
      }
    }
    node = *res;
  }
  return *res;
}

void PNS::expandNode(Node& node, helper::PLAYER root_player) {
  node.generateChildren();

  std::cerr << "expanding " << node.game_.toString() << std::endl;
  std::cerr << " node type = " << node.type_ << std::endl;

  for (auto& child : node.children_) {
    child.evaluate(root_player);
    setProofAndDisproofNumbers(child);

    std::cerr << "child = " << child.game_.toString() << " - child.pn = " << child.pn_ << ", child.dn = " << child.dn_ << std::endl;

    if ((node.type_ == helper::PLAYER::WHITE && child.pn_ == 0) ||
        (node.type_ == helper::PLAYER::BLACK && child.dn_ == 0)) {
      break;
    }
  }
}

Node& PNS::updateAncestors(Node& node, Node& root) {
  std::cerr << "updateAncestors for " << node.game_.toString() << std::endl;
  while (true) {
    uint16_t old_pn = node.pn_;
    uint16_t old_dn = node.dn_;

    std::cerr << "  node.game = " << node.game_.toString() << ",  root.game = " << root.game_.toString() << std::endl;
    std::cerr << "  node.id   = " << node.id_ << ",  root.id   = " << root.id_ << std::endl;

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
