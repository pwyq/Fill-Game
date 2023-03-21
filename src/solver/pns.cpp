/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 17:05:59
 * @modify date 2023-03-21 15:23:22
 */

#include "solver/pns.h"
// std
#include <iostream>
// local
#include "solver/game.h"
#include "solver/node.h"

namespace solver {
namespace pns {

PNS::PNS(const Game& game) {
  root_ = new Node(game, helper::NODE_TYPE::OR, nullptr, helper::PLAYER::BLACK);
}

short PNS::getResult() {
  return solveGame(root_);
}

short PNS::solveGame(Node* root) {
  if (root->game_.isTerminal()) {
    return -1;
  }
  root->evaluate();
  setProofAndDisproofNumbers(root);
  Node* curr = root;
  while (root->pn_ != 0 && root->dn_ != 0) {
    Node* mpn = selectMostProvingNode(curr);
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

void PNS::setProofAndDisproofNumbers(Node* node) {
  if (node->is_expanded_) {
    if (node->type_ == helper::NODE_TYPE::AND) {
      node->pn_ = 0;
      node->dn_ = INF;
      Node* n   = node->children;
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
      Node* n   = node->children;
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

/**
 * @brief Find the node 
 *            with minimum disproven number for AND nodes
 *            with minimum proven number for OR nodes
 * @param node 
 * @return Node& 
 */
Node* PNS::selectMostProvingNode(Node* node) {
  while (node->is_expanded_) {
    Node* n = node->children;
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

void PNS::expandNode(Node* node) {
  generateChildren(node);

  Node* n = node->children;
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

Node* PNS::updateAncestors(Node* node, Node* root) {
  // https://stackoverflow.com/questions/12446586/local-variables-defined-inside-for-loops-in-c
  //  performance won't be much a difference if we defined old_pn/old_dn outside the loop
  do {
    uint32_t old_pn = node->pn_;
    uint32_t old_dn = node->dn_;
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

void PNS::generateChildren(Node* node) {
  auto possible_moves = node->game_.getPossibleMoves();

  for (auto& pm : possible_moves) {
    for (auto& v : pm.second) {
      if (node->type_ == helper::NODE_TYPE::OR) {
        node->addChild(new Node(node->game_, pm.first, v, helper::NODE_TYPE::AND, node, changePlayer(node->player_)));
      } else {
        node->addChild(new Node(node->game_, pm.first, v, helper::NODE_TYPE::OR, node, changePlayer(node->player_)));
      }
    }
  }
}

helper::PLAYER PNS::changePlayer(helper::PLAYER player) {
  return (player == helper::PLAYER::BLACK) ? helper::PLAYER::WHITE : helper::PLAYER::BLACK;
}

}  // namespace pns
}  // namespace solver
