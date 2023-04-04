/**
 * @author    Junwen Shen
 * @create date 2023-04-03 10:25:11
 * @modify date 2023-04-04 13:35:11
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
  helper::Move bestMove();

 private:
  std::mt19937 rng_{std::random_device{}()};
  double exploration_const_ = 1.414;
  size_t num_simulations_;
  [[nodiscard]] std::shared_ptr<Node> selectBestChild(const std::shared_ptr<Node>& node) const;
  bool simulate(const std::shared_ptr<Node>& node);
  static void backpropagation(const std::shared_ptr<Node>& node, bool win);
  static std::shared_ptr<Node> expand(const std::shared_ptr<Node>& node);
};

}  // namespace solver::mcts

#endif  // FG_SOLVER_MCTS_H_
