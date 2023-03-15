/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-15 13:57:46
 * @modify date 2023-03-15 13:57:46
 * @desc Minimax implementation
 */

#ifndef FG_SOLVER_MINIMAX_H_
#define FG_SOLVER_MINIMAX_H_
//local
#include "node.h"

namespace solver {
namespace minimax {

class Minimax {
 public:
  explicit Minimax();
  void solve();

 private:
  int MinimaxOR();
  int MinimaxAND();
};

}  // namespace minimax
}  // namespace solver

#endif  // FG_SOLVER_MINIMAX_H_