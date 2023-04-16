/**
 * @author    Junwen Shen, Yanqing Wu
 * @create date 2023-04-03 10:22:24
 * @modify date 2023-04-04 16:30:16
 *
 */
// local
#include "solver/mcts.h"

#include <iostream>

namespace solver::mcts {

MCTS::MCTS(const Game& game) {
  root_       = std::make_shared<Node>(game);
  node_count_ = 0;
}

std::shared_ptr<Node> MCTS::selectBestChild(const std::shared_ptr<Node>& node) const {
  double best_uct                  = -INF_SHORT;
  std::shared_ptr<Node> best_child = nullptr;

  for (const auto& child : node->children_) {
    // UCT = exploitation + exploration
    if (child->visits_ == 0) {
      // For exploration, its UCT is infty now. It's automatically the best
      return child;
    }
    double uct = (static_cast<double>(child->wins_) / child->visits_)                         // exploitation (win rate)
                 + exploration_const_ * std::sqrt(std::log(node->visits_) / child->visits_);  // exploration
    if (uct > best_uct) {
      best_uct   = uct;
      best_child = child;
    }
  }
  return best_child;
}

std::shared_ptr<Node> MCTS::selectFinalChild(const std::shared_ptr<Node>& node) const {
  double highest_visit_count       = -INF_SHORT;
  double highest_num_wins          = -INF_SHORT;
  std::shared_ptr<Node> best_child = nullptr;

  for (const auto& child : node->children_) {
    if (child->visits_ > highest_visit_count) {
      highest_visit_count = child->visits_;
      highest_num_wins    = child->wins_;
      best_child          = child;
    } else if (child->visits_ == highest_visit_count) {
      // There's a tie. We break it using the win-rate, which is equivalent to breaking it using child_wins_
      if (child->wins_ > highest_num_wins) {
        highest_num_wins = child->wins_;
        best_child       = child;
      }
    }
  }
  return best_child;
}

void MCTS::backpropagation(const std::shared_ptr<Node>& node, bool win) {
  std::shared_ptr<Node> current = node;
  while (current) {
    current->visits_++;
    if (win) {
      current->wins_++;
    }
    current = current->parent().lock();
  }
}

std::shared_ptr<Node> MCTS::expand(const std::shared_ptr<Node>& node) {
  auto moves = node->game().getPossibleMoves();

  for (const auto& move : moves) {
    ++node_count_;
    auto child = std::make_shared<Node>(node->game(), move.first, move.second, node);
    node->children_.push_back(child);
  }

  return node->children_.empty() ? nullptr : node->children_.front();
}

bool MCTS::simulate(const std::shared_ptr<Node>& node) {
  Game* game = new Game(node->game());
  while (!game->isTerminal()) {
    auto moves = game->getPossibleMoves();
    std::uniform_int_distribution<> dist(0, moves.size() - 1);
    auto move = moves[dist(rng_)];
    game->unsafePlay(move.first, move.second);

    Game* temp = game;
    game       = new Game(temp->toString());
    delete temp;
  }
  return root_->game().toPlay() != game->toPlay();  // Is it a win for the root?
}

/**
 * @brief Perform Search. Store the best move if found one; otherwise store Move{{0,0}, 0}
 *
 */
void MCTS::search() {
  node_count_ = 1;
  if (root_->game().isTerminal()) {
    best_move_ = helper::Move{{0, 0}, 0};
    return;
  }
  num_simulations_ = root_->game().getPossibleMoves().size() * 1000;
  expand(root_);
  for (size_t i = 0; i < num_simulations_; ++i) {
    auto node = root_;
    while (!node->children_.empty()) {
      node = selectBestChild(node);
    }

    auto expanded = expand(node);
    if (expanded) {
      node = expanded;
    }

    bool win = MCTS::simulate(node);
    backpropagation(node, win);
  }
  auto best_child = selectFinalChild(root_);

  best_move_ = best_child->move();
  return;
}

}  // namespace solver::mcts
