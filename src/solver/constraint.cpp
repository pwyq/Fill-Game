/**
 * @author      Yanqing Wu, Junwen Shen
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:33:32
 * @modify date 2023-02-10 05:33:32
 */
#include "solver/constraint.h"
// std
#include <csignal>
#include <cstring>
#include <iostream>

namespace Solver {

Constraint::Constraint(size_t memory_limit, size_t time_limit)
    : memory_limit({memory_limit, memory_limit + SIGSTKSZ}),
      time_limit({time_limit, time_limit + 1}) {}

void Constraint::apply() {
  setSigStack();
  if (setrlimit(RLIMIT_AS, &memory_limit) != 0) {
    std::cerr << "setrlimit failed" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (setrlimit(RLIMIT_CPU, &time_limit) != 0) {
    std::cerr << "setrlimit failed" << std::endl;
    exit(EXIT_FAILURE);
  }
}

static inline void set_sigaction(int signal, const struct sigaction *action) {
  if (sigaction(signal, action, nullptr) == -1) {
    std::cerr << "sigaction failed" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Constraint::setSigStack() {
  stack_t sigstack;
  sigstack.ss_sp = malloc(SIGSTKSZ);
  if (sigstack.ss_sp == nullptr) {
    std::cerr << "malloc failed" << std::endl;
    exit(EXIT_FAILURE);
  }
  sigstack.ss_size = SIGSTKSZ;
  sigstack.ss_flags = 0;
  if (sigaltstack(&sigstack, nullptr) == -1) {
    std::cerr << "sigaltstack failed" << std::endl;
    exit(EXIT_FAILURE);
  }
  struct sigaction sa {};
  sa.sa_flags = SA_ONSTACK;
  sigemptyset(&sa.sa_mask);
  sa.sa_handler = *signalHandler.target<void (*)(int)>();
  set_sigaction(SIGSEGV, &sa);
  set_sigaction(SIGXCPU, &sa);
  set_sigaction(SIGALRM, &sa);
}

}  // namespace Solver
