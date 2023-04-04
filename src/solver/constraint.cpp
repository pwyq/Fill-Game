/**
 * @author      Yanqing Wu, Junwen Shen
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:33:32
 * @modify date 2023-02-10 05:33:32
 */
#ifdef __linux__
#include "solver/constraint.h"
// std
#include <csignal>
#include <iostream>

namespace solver {

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

}  // namespace solver
#elif _WIN32

#include "solver/constraint.h"
#include <iostream>

namespace solver {

Constraint::Constraint(size_t memory_limit, size_t time_limit)
    : time_limit(time_limit) {
  GetSystemInfo(&systemInfo);
  if (memory_limit < 20 * systemInfo.dwPageSize) {
    memory_limit = 20 * systemInfo.dwPageSize;
  }
  this->memory_limit = memory_limit;
}

Constraint::~Constraint() {
  CancelWaitableTimer(hTimer);
  if (hTimer != nullptr) {
    CloseHandle(hTimer);
  }
}

void Constraint::apply() {
  SetProcessWorkingSetSize(GetCurrentProcess(), systemInfo.dwPageSize, memory_limit);
  hTimer = CreateWaitableTimer(nullptr, TRUE, "Time Constraint");
  if (hTimer == nullptr) {
    std::cerr << "CreateWaitableTimer failed" << std::endl;
    exit(EXIT_FAILURE);
  }
  LARGE_INTEGER liDueTime;
  long long qwDueTime = -(long long)(time_limit * SECOND);
  liDueTime.LowPart = (DWORD)(qwDueTime & 0xFFFFFFFF);
  liDueTime.HighPart = (LONG)(qwDueTime >> 32);
  if (!SetWaitableTimer(hTimer, &liDueTime, 0, *timerAPCProc.target<PTIMERAPCROUTINE>(), nullptr, FALSE)) {
    std::cerr << "SetWaitableTimer failed" << std::endl;
    exit(EXIT_FAILURE);
  }
}
}  // namespace solver
#endif
