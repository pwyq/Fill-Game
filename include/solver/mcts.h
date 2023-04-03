/**
 * @author    Junwen Shen
 * @create date 2023-04-03 10:25:11
 * @modify date 2023-04-03 10:25:11
 *
 */
#ifndef FG_SOLVER_MCTS_H_
#define FG_SOLVER_MCTS_H_

// std
#include <random>
// local
#include "node.h"

namespace solver::mcts {

class MCTS {
 public:
  std::shared_ptr<solver::mcts::Node> root_;
  explicit MCTS(const Game& game);
  solver::helper::Move search();

 private:
  std::mt19937 rng_{std::random_device{}()};
  static constexpr double C = 1.414;  // exploration constant
  static constexpr size_t N = 1000;    // number of simulations
  static std::shared_ptr<Node> select_best_child(const std::shared_ptr<Node>& node);
  bool simulate(const std::shared_ptr<Node>& node);
  static void backpropagation(const std::shared_ptr<Node>& node, bool win);
  static std::shared_ptr<Node> expand(const std::shared_ptr<Node>& node);
};
}

#endif  // FG_SOLVER_MCTS_H_
