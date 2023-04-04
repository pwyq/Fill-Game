/**
 * @author    Junwen Shen, Yanqing Wu
 * @create date 2023-04-03 10:22:24
 * @modify date 2023-04-04 16:30:16
 *
 */
//local
#include "solver/mcts.h"

#include <iostream>

namespace solver::mcts {

MCTS::MCTS(const Game& game) {
  root_ = std::make_shared<Node>(game);
}

std::shared_ptr<Node> MCTS::selectBestChild(const std::shared_ptr<Node>& node) const {
  double best_uct                  = -INF_SHORT;
  std::shared_ptr<Node> best_child = nullptr;

  for (const auto& child : node->children_) {
    // UCT = exploitation + exploration
    double uct = (static_cast<double>(child->wins_) / child->visits_)                         // exploitation (win rate)
                 + exploration_const_ * std::sqrt(std::log(node->visits_) / child->visits_);  // exploration
    if (uct > best_uct) {
      best_uct   = uct;
      best_child = child;
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
    win     = !win;
    current = current->parent_.lock();
  }
}

std::shared_ptr<Node> MCTS::expand(const std::shared_ptr<Node>& node) {
  auto moves = node->game_.getPossibleMoves();

  for (const auto& move : moves) {
    auto child = std::make_shared<Node>(node->game_, move.first, move.second, node);
    node->children_.push_back(child);
  }

  return node->children_.empty() ? nullptr : node->children_.front();
}

bool MCTS::simulate(const std::shared_ptr<Node>& node) {
  Game game(node->game_);
  while (!game.isTerminal()) {
    auto moves = game.getPossibleMoves();
    std::uniform_int_distribution<> dist(0, moves.size() - 1);
    auto move = moves[dist(rng_)];
    game.unsafePlay(move.first, move.second);
  }
  return root_->game_.toPlay() != game.toPlay();
}

/**
 * @brief Perform Search. Store the best move if found one; otherwise store Move{{0,0}, 0}
 * 
 */
void MCTS::search() {
  if (root_->game_.isTerminal()) {
    best_move_ = helper::Move{{0, 0}, 0};
    return;
  }

  num_simulations_ = root_->game_.getPossibleMoves().size() * 1000;
  mcts::MCTS::expand(root_);
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
  auto best_child = selectBestChild(root_);

  best_move_ = best_child->move_;
  return;
}

}  // namespace solver::mcts
