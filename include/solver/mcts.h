/**
 * @author    Junwen Shen, Yanqing Wu, Luke Kapeluck
 * @create date 2023-04-03 10:25:11
 * @modify date 2023-04-06 23:00:00
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

  void search();
  inline helper::Move bestMove() const { return best_move_; }

  size_t getNodeCount() const {
    return node_count_;
  };

 private:
  std::mt19937 rng_{std::random_device{}()};
  double exploration_const_ = 1.414;
  size_t num_simulations_;
  helper::Move best_move_;  // used for selecting next move when playing against Human/Other AI
  size_t node_count_;

  [[nodiscard]] std::shared_ptr<Node> selectBestChild(const std::shared_ptr<Node>& node) const;
  [[nodiscard]] std::shared_ptr<Node> selectFinalChild(const std::shared_ptr<Node>& node) const;
  bool simulate(const std::shared_ptr<Node>& node);
  static void backpropagation(const std::shared_ptr<Node>& node, bool win);
  std::shared_ptr<Node> expand(const std::shared_ptr<Node>& node);
};

}  // namespace solver::mcts

#endif  // FG_SOLVER_MCTS_H_
