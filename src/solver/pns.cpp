/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 17:05:59
 * @modify date 2023-03-21 17:59:50
 */

#include "solver/pns.h"
// std
#include <iostream>
// local
#include "solver/game.h"
#include "solver/pns_node.h"

namespace solver::pns {

PNS::PNS(const Game& game) {
  root_       = new Node(game, helper::NODE_TYPE::OR, nullptr, helper::PLAYER::BLACK);
  best_move_  = helper::Move{Pos{0, 0}, 0};
  node_count_ = 0;
}

short PNS::getResult(helper::PLAYER root_player) {
  node_count_ = 0;
  return solve(root_, root_player);
}

short PNS::solve(Node* root, helper::PLAYER player) {
  ++node_count_;

  if (root->game().isTerminal()) {
    return -1;
  }
  root->evaluate();
  root->setProofAndDisproofNumbers();
  Node* curr = root;
  while (root->pn() != 0 && root->dn() != 0) {
    Node* mpn = selectMostProvingNode(curr);
    expandNode(mpn);
    curr = updateAncestors(mpn, root);
  }

  if (root->pn() == 0) {
    return (root->player() == player) ? 1 : -1;
  } else if (root->dn() == 0) {
    return (root->player() == player) ? -1 : 1;
  } else {
    return 0;
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
  while (node->isExpanded()) {
    Node* n = node->children();
    if (node->type() == helper::NODE_TYPE::OR) {
      while (n->pn() != node->pn()) {
        n = n->sibling();
      }
    } else {
      while (n->dn() != node->dn()) {
        n = n->sibling();
      }
    }
    node = n;
  }
  return node;
}

void PNS::expandNode(Node* node) {
  generateChildren(node);

  Node* n = node->children();
  while (n != nullptr) {
    n->evaluate();
    n->setProofAndDisproofNumbers();
    if (best_move_.value == 0 && n->value() == helper::PROOF_VALUE::WIN) {
      best_move_ = n->move();
    }
    if ((node->type() == helper::NODE_TYPE::OR && n->pn() == 0) ||
        (node->type() == helper::NODE_TYPE::AND && n->dn() == 0)) {
      break;
    }
    n = n->sibling();
  }
  node->setExpanded(true);
}

Node* PNS::updateAncestors(Node* node, Node* root) {
  // https://stackoverflow.com/questions/12446586/local-variables-defined-inside-for-loops-in-c
  //  performance won't be much a difference if we defined old_pn/old_dn outside the loop
  do {
    uint32_t old_pn = node->pn();
    uint32_t old_dn = node->dn();
    node->setProofAndDisproofNumbers();
    if (node->pn() == old_pn && node->dn() == old_dn) {
      return node;
    }
    if (node->pn() == 0 || node->dn() == 0) {
      node->deleteSubtree();
    }
    if (node == root) {
      return node;
    }
    node = node->parent();
  } while (true);
}

void PNS::generateChildren(Node* node) {
  auto possible_moves = node->game().getPossibleMoves();

  for (auto& pm : possible_moves) {
    ++node_count_;
    if (node->type() == helper::NODE_TYPE::OR) {
      node->addChild(new Node(node->game(), pm.first, pm.second, helper::NODE_TYPE::AND, node, helper::changePlayer(node->player())));
    } else {
      node->addChild(new Node(node->game(), pm.first, pm.second, helper::NODE_TYPE::OR, node, helper::changePlayer(node->player())));
    }
  }
}

/**
 * @brief Return the first move that result in a WIN
 *        if not found
 *          no time limit, resign (return a dummy value) {{0,0}, 0}
 *          has time limit, return a random move that hasn't been examined? (TODO? this case)
 *
 * @return helper::Move
 */
helper::Move PNS::bestMove() const {
  // if has time limit (the agent is probably forced to stop) return a random move
  //  TODO
  return best_move_;
}

}  // namespace solver::pns
