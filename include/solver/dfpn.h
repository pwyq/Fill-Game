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
#include "constraint.h"

namespace solver::dfpn {

extern helper::Timer<> g_timer;
extern size_t g_counter;

class DFPN {
 public:
  explicit DFPN(const Game &game);

  void solve();
  short getResult() const;
  std::string formatResult() const;
#if defined(__linux__)
  static void signalHandler(int signum);
#endif
  [[maybe_unused]] static void setConstraint(Constraint &constraint);

  inline helper::PROOF_VALUE result() const { return result_; }
  inline helper::Move bestMove() const { return best_move_; }

 private:
  Node root_;
  helper::PROOF_VALUE result_ = helper::UNKNOWN;
  helper::Move best_move_;  // used for selecting next move when playing against Human/Other AI
  std::unordered_map<std::string, std::pair<uint32_t, uint32_t>> tt_;

  void MID(Node &node);
  size_t selectChild(Node &node, uint32_t &child_phi, uint32_t &delta_2);
  void saveProofAndDisproofNumbers(Node &node, uint32_t phi, uint32_t delta);
  inline void retrieveProofAndDisproofNumbers(Node &node, uint32_t &phi, uint32_t &delta);

  uint32_t computeMinDelta(Node &node);
  uint32_t computeSumPhi(Node &node);
};

// inline function declaration
inline void DFPN::saveProofAndDisproofNumbers(Node &node, uint32_t phi, uint32_t delta) {
  tt_[node.id_] = std::make_pair(phi, delta);
}

}  // namespace solver::dfpn

#endif  // FG_SOLVER_DFPN_H_
