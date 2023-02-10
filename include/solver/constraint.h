/**
 * @author      Junwen Shen, Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:28:28
 * @modify date 2023-02-10 05:28:28
 * @desc Apply memory limit and time limit to the search algorithm
 */
#ifndef FG_SOLVER_CONSTRAINT_H
#define FG_SOLVER_CONSTRAINT_H
// Std
#include <sys/resource.h>

#include <csignal>
#include <cstdlib>
#include <functional>

namespace Solver {

class Constraint {
 public:
  Constraint(size_t memory_limit, size_t time_limit);

  void apply();

  std::function<void(int)> signalHandler;

 private:
  struct rlimit memory_limit;
  struct rlimit time_limit;

  void setSigStack();
};

}  // namespace Solver

#endif  // FG_SOLVER_CONSTRAINT_H