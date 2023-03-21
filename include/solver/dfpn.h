/**
 * @author      Yanqing Wu, Junwen Shen, Luke Kapeluck
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:29:17
 * @modify date 2023-03-21 16:06:37
 * @desc Depth First Proof Number Search
 */
#ifndef FG_SOLVER_DFPN_H_
#define FG_SOLVER_DFPN_H_
// std
#include <unordered_map>
#include <utility>
// local
#include "node.h"

namespace solver {
namespace dfpn {

extern helper::Timer<> g_timer;
extern size_t g_counter;

class DFPN {
 public:
  explicit DFPN(const Game &game);

  void solve();
  void MID(Node &node);
  std::string formatResult() const;
  static void signalHandler([[maybe_unused]] int signum);

  Node root() const { return root_; }
  helper::PROOF_VALUE result() const { return result_; }
  helper::Move best_move() const { return best_move_; }

 private:
  size_t selectChild(Node &node, uint32_t &child_phi, uint32_t &delta_2);
  std::unordered_map<std::string, std::pair<uint32_t, uint32_t>> tt_;
  void saveProofAndDisproofNumbers(Node &node, uint32_t phi, uint32_t delta);
  inline void retrieveProofAndDisproofNumbers(Node &node, uint32_t &phi, uint32_t &delta);

  uint32_t computeMinDelta(Node &node);
  uint32_t computeSumPhi(Node &node);

  Node root_;
  helper::PROOF_VALUE result_ = helper::UNKNOWN;
  helper::Move best_move_;  // Assignment 1 requirement; also used for selecting next move when playing against Human/Other AI
};

// inline function declaration
inline void DFPN::saveProofAndDisproofNumbers(Node &node, uint32_t phi,
                                              uint32_t delta) {
  tt_[node.id_] = std::make_pair(phi, delta);
}

}  // namespace dfpn
}  // namespace solver

#endif  // FG_SOLVER_DFPN_H_