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
  // Node* root_ptr = &root_;
  Node* current = &root_;

  setProofAndDisproofNumbers(current);
  if (!(root_.pn_ == 1 && root_.dn_ == 1)) {  // delete later
    return -999;
  }

  // point to the same object
  // Node current = root_;
  // Node* current = &root_;
  // std::cerr << &root_ << " vs. " << &current << std::endl;
  Node* most_proving_node = nullptr;
  while (root_.pn_ != 0 && root_.dn_ != 0) {
    std::cerr << "\n\n=====================================================\n";
    std::cerr << "root.pn = " << root_.pn_ << ", root.dn = " << root_.dn_ << std::endl;
    most_proving_node = selectMostProvingNode(current);
    std::cerr << "getting mpn addr = " << most_proving_node << " , id = " << most_proving_node->game_.toString() << std::endl;
    std::cerr << current->game_.toString() << " --> " << most_proving_node->game_.toString() << std::endl;

    expandNode(most_proving_node, root_player);
    current = updateAncestors(most_proving_node);
  }

  if (root_.pn_ == 0) {
    return 1;
  } else if (root_.dn_ == 0) {
    return -1;
  } else {
    return 0;
  }
}

void PNS::setProofAndDisproofNumbers(Node* node) {
  std::cerr << "setProofAndDisproofNumbers for " << node->game_.toString() << "    " << node << std::endl;
  if (node->is_expanded_) {
    std::cerr << "  node is expanded...\n";
    // internal nodes

    if (node->type_ == helper::PLAYER::WHITE) {  // AND type (0)
      std::cerr << "  node is AND node\n";
      node->pn_ = 0;
      node->dn_ = INF;
      // N.pn = sum of children's PN, N.dn = min of children's dn
      for (auto& child : node->children_) {
        std::cerr << "  before " << +node->pn_ << ", " << +node->dn_ << std::endl;
        node->pn_ += child.pn_;
        if (child.dn_ < node->dn_) {
          node->dn_ = child.dn_;
        }
        std::cerr << "  after  " << +node->pn_ << ", " << +node->dn_ << std::endl;
      }
    } else {  // OR type (1)
      std::cerr << "  node is OR node\n";

      node->pn_ = INF;
      node->dn_ = 0;
      // N.pn = min of children's PN, N.dn = sum of children's dn
      for (auto& child : node->children_) {
        std::cerr << "  before " << +node->pn_ << ", " << +node->dn_ << std::endl;
        node->dn_ += child.dn_;
        if (child.pn_ < node->pn_) {
          node->pn_ = child.pn_;
        }
        std::cerr << "  after  " << +node->pn_ << ", " << +node->dn_ << std::endl;
      }
    }
  } else {
    // terminal / non-terminal leaf
    std::cerr << "  node type = " << node->type_ << ", node value = " << node->value_ << "\n";
    switch (node->value_) {
      case helper::PROOF_VALUE::WIN:  // PROVEN
        node->pn_ = 0;
        node->dn_ = INF;
        break;
      case helper::PROOF_VALUE::LOSS:  // DISPROVEN
        node->pn_ = INF;
        node->dn_ = 0;
        break;
      case helper::PROOF_VALUE::UNKNOWN:
        node->pn_ = 1;
        node->dn_ = 1;
        break;
      default:
        break;
    }
  }
  std::cerr << "  after setting, node.pn = " << node->pn_ << ", node.dn = " << node->dn_ << "\n\n";
}

/**
 * @brief Find the node 
 *            with minimum disproven number for AND nodes
 *            with minimum proven number for OR nodes
 * @param node 
 * @return Node& 
 */
Node* PNS::selectMostProvingNode(Node* node) {
  std::cerr << "selectMostProvingNode for " << node << ", type = " << node->type_ << std::endl;
  Node* new_node = &(*node);
  Node* res      = node;
  while (new_node->is_expanded_) {
    uint16_t value = INF;
    if (new_node->type_ == helper::PLAYER::BLACK) {  // OR type (1)
      for (auto& child : new_node->children_) {
        std::cerr << "  child = " << &child << ", pn = " << +child.pn_ << ", dn = " << +child.dn_ << std::endl;
        if (value > child.pn_) {
          value = child.pn_;
          res   = &child;
          std::cerr << "    ! updating return to " << &child << ", checking if res been updated, res = " << res << std::endl;
          std::cerr << "    ! child.game = " << child.game_.toString() << ", res.game = " << res->game_.toString() << std::endl;
        }
      }
    } else {  // AND type (0)
      for (auto& child : new_node->children_) {
        std::cerr << "  child = " << &child << ", pn = " << +child.pn_ << ", dn = " << +child.dn_ << std::endl;
        if (value > child.dn_) {
          value = child.dn_;
          res   = &child;
          std::cerr << "    ! updating return to " << &child << ", checking if res been updated, res = " << res << std::endl;
          std::cerr << "    ! child.game = " << child.game_.toString() << ", res.game = " << res->game_.toString() << std::endl;
        }
      }
    }
    std::cerr << "  @fishy before " << new_node << " =?= " << res << std::endl;
    new_node = res;
    std::cerr << "  @fishy after  " << new_node << " =?= " << res << std::endl;
  }
  std::cerr << "node addr = " << node << std::endl;
  std::cerr << +node->pn_ << ", " << +node->dn_ << " vs. " << +res->pn_ << ", " << +res->dn_ << std::endl;
  std::cerr << "new_node addr = " << new_node << std::endl;
  std::cerr << +new_node->pn_ << ", " << +new_node->dn_ << " vs. " << +res->pn_ << ", " << +res->dn_ << std::endl;
  std::cerr << "returning node addr = " << res << ", id = " << res->game_.toString() << std::endl;
  return res;
  // return node;
}

void PNS::expandNode(Node* node, helper::PLAYER root_player) {
  node->generateChildren();

  std::cerr << "expanding " << node->game_.toString() << " " << node << std::endl;
  std::cerr << " node type = " << node->type_ << " , children.size = " << node->children_.size() << std::endl;

  for (auto& child : node->children_) {
    child.evaluate(root_player);
    Node* tmp = &child;
    setProofAndDisproofNumbers(tmp);

    std::cerr << "child = " << &child << ", ";
    std::cerr << "child = " << child.game_.toString() << " - child.pn = " << child.pn_ << ", child.dn = " << child.dn_ << std::endl;

    if ((node->type_ == helper::PLAYER::BLACK && child.pn_ == 0) ||
        (node->type_ == helper::PLAYER::WHITE && child.dn_ == 0)) {
      break;
    }
  }
}

Node* PNS::updateAncestors(Node* node) {
  std::cerr << "updateAncestors for " << node->game_.toString() << std::endl;
  while (true) {
    uint16_t old_pn = node->pn_;
    uint16_t old_dn = node->dn_;

    std::cerr << "  node.game = " << node->game_.toString() << ",  root.game = " << root_.game_.toString() << std::endl;
    std::cerr << "  node.id   = " << node->id_ << ",  root.id   = " << root_.id_ << std::endl;

    setProofAndDisproofNumbers(node);

    if (old_pn == node->pn_ && old_dn == node->dn_) {
      std::cerr << "    old == now, return\n";
      return node;
    } else {
      std::cerr << "    old_pn = " << +old_pn << ", old_dn = " << +old_dn << std::endl;
      std::cerr << "    now_dn = " << +node->pn_ << ", now_dn = " << +node->dn_ << std::endl;
    }

    // if (node.id_ == root_.id_) {
    // if (&node == &root_) {  // comparing the address instead of the id_
    if (node == &root_) {  // comparing the address instead of the id_
      std::cerr << "    node == root, return\n";
      return node;
    }

    std::cerr << "    before go to parent, node = " << node << " , id = " << node->id_ << std::endl;
    node = node->parent_;
    std::cerr << "    after  go to parent, node = " << node << " , id = " << node->id_ << std::endl;
  }
}

////////////////////////////////////////////////////////////////

PNS2::PNS2(const Game& game) {
  root_ = new Node2(game, helper::NODE_TYPE::OR, nullptr, helper::PLAYER::BLACK);
}

short PNS2::getResult() {
  return solveGame(root_);
}

short PNS2::solveGame(Node2* root) {
  if (root->game_.isTerminal()) {
    return -1;
  }
  root->evaluate();
  setProofAndDisproofNumbers(root);
  Node2* curr = root;
  while (root->pn_ != 0 && root->dn_ != 0) {
    Node2* mpn = selectMostProvingNode(curr);
    expandNode(mpn);
    curr = updateAncestors(mpn, root);
  }

  if (root->pn_ == 0) {
    return 1;
  } else if (root->dn_ == 0) {
    return -1;
  } else {
    return 0;
  }
}

void PNS2::setProofAndDisproofNumbers(Node2* node) {
  if (node->is_expanded_) {
    if (node->type_ == helper::NODE_TYPE::AND) {
      node->pn_ = 0;
      node->dn_ = INF;
      Node2* n  = node->children;
      while (n != nullptr) {
        node->pn_ += n->pn_;
        if (n->dn_ < node->dn_) {
          node->dn_ = n->dn_;
        }
        n = n->sibling;
      }
    } else {
      node->pn_ = INF;
      node->dn_ = 0;
      Node2* n  = node->children;
      while (n != nullptr) {
        node->dn_ += n->dn_;
        if (n->pn_ < node->pn_) {
          node->pn_ = n->pn_;
        }
        n = n->sibling;
      }
    }
  } else {
    switch (node->value_) {
      case helper::PROOF_VALUE::WIN:
        node->pn_ = 0;
        node->dn_ = INF;
        break;
      case helper::PROOF_VALUE::LOSS:
        node->pn_ = INF;
        node->dn_ = 0;
        break;
      case helper::PROOF_VALUE::UNKNOWN:
        node->pn_ = 1;
        node->dn_ = 1;
        break;
    }
  }
}

Node2* PNS2::selectMostProvingNode(Node2* node) {
  while (node->is_expanded_) {
    Node2* n = node->children;
    if (node->type_ == helper::NODE_TYPE::OR) {
      while (n->pn_ != node->pn_) {
        n = n->sibling;
      }
    } else {
      while (n->dn_ != node->dn_) {
        n = n->sibling;
      }
    }
    node = n;
  }
  return node;
}

void PNS2::expandNode(Node2* node) {
  generateChildren(node);

  Node2* n = node->children;
  while (n != nullptr) {
    n->evaluate();
    setProofAndDisproofNumbers(n);
    if ((node->type_ == helper::NODE_TYPE::OR && node->pn_ == 0) ||
        (node->type_ == helper::NODE_TYPE::AND && node->dn_ == 0)) {
      break;
    }
    n = n->sibling;
  }
  node->is_expanded_ = true;
}

Node2* PNS2::updateAncestors(Node2* node, Node2* root) {
  do {
    int old_pn = node->pn_;
    int old_dn = node->dn_;
    setProofAndDisproofNumbers(node);
    if (node->pn_ == old_pn && node->dn_ == old_dn) {
      return node;
    }
    if (node->pn_ == 0 || node->dn_ == 0) {
      node->deleteSubtree();
    }
    if (node == root) {
      return node;
    }
    node = node->parent_;
  } while (true);
}

void PNS2::generateChildren(Node2* node) {
  auto possible_moves = node->game_.getPossibleMoves();

  for (auto& pm : possible_moves) {
    for (auto& v : pm.second) {
      if (node->type_ == helper::NODE_TYPE::OR) {
        node->addChild(new Node2(node->game_, pm.first, v, helper::NODE_TYPE::AND, node, changePlayer(node->player_)));
      } else {
        node->addChild(new Node2(node->game_, pm.first, v, helper::NODE_TYPE::OR, node, changePlayer(node->player_)));
      }
    }
  }
}

helper::PLAYER PNS2::changePlayer(helper::PLAYER player) {
  return (player == helper::PLAYER::BLACK) ? helper::PLAYER::WHITE : helper::PLAYER::BLACK;
}

}  // namespace pns
}  // namespace solver
