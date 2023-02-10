#ifndef FG_SOLVER_CONSTRAINT_H
#define FG_SOLVER_CONSTRAINT_H

#include <csignal>
#include <cstdlib>
#include <functional>
#include <sys/resource.h>

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

} // namespace Solver

#endif // FG_SOLVER_CONSTRAINT_H