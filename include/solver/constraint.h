/**
 * @author      Junwen Shen, Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:28:28
 * @modify date 2023-02-10 05:28:28
 * @desc Apply memory limit and time limit to the bestMove algorithm
 */
#ifndef FG_SOLVER_CONSTRAINT_H
#define FG_SOLVER_CONSTRAINT_H

#ifdef __linux__
// Std
#include <sys/resource.h>

#include <csignal>
#include <cstdlib>
#include <functional>

namespace solver {

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

}  // namespace solver
#elif _WIN32
#include <Windows.h>

#include <functional>

namespace solver {

class Constraint {
 public:
  Constraint(size_t memory_limit, size_t time_limit);
  ~Constraint();
  void apply();
  std::function<void(LPVOID, DWORD, DWORD)> timerAPCProc;

 private:
  constexpr static size_t SECOND = 10000000;
  _SYSTEM_INFO systemInfo        = SYSTEM_INFO();
  HANDLE hTimer                  = nullptr;
  size_t memory_limit;
  size_t time_limit;
};
}  // namespace solver
#endif

#endif  // FG_SOLVER_CONSTRAINT_H
