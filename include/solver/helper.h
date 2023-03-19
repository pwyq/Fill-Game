/**
 * @author      Yanqing Wu, Junwen Shen
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:30:34
 * @modify date 2023-03-18 17:29:04
 */
#ifndef FG_SOLVER_HELPER_H_
#define FG_SOLVER_HELPER_H_
// std
#include <cassert>
#include <chrono>
#include <functional>
#include <string>

namespace solver {
namespace helper {

#define INF UINT16_MAX
#define INF_SHORT 32767  // SHRT_MAX

struct Pos {
  uint8_t row : 4 {};
  uint8_t col : 4 {};
  bool is_important = false;

  inline bool operator==(const Pos &other) const {
    return row == other.row && col == other.col;
  }

  [[nodiscard]] std::string toString() const {
    return std::to_string((unsigned int)col) + " " +
           std::to_string((unsigned int)row);
  }

  struct Hash {
    std::size_t operator()(const Pos &pos) const {
      return std::hash<uint8_t>()((pos.row << 4) | pos.col);
    }
  };
};

struct Move {
  Pos pos{};
  uint8_t value = 0;

  [[nodiscard]] std::string toString() const {
    return pos.toString() + " " + std::to_string((unsigned int)value);
  }
};

enum PLAYER {
  BLACK = 0,  // AND
  WHITE = 1   // OR
};

enum PROOF_VALUE {
  WIN     = 1,  // PROVEN
  LOSS    = 0,  // DISPROVEN
  UNKNOWN = -1  // UNKNOWN
};

// https://stackoverflow.com/a/21995693
template <class ClockT = std::chrono::steady_clock>
class Timer {
  using time_point = typename ClockT::time_point;

 protected:
  time_point start_ = ClockT::now();
  time_point end_   = {};

 public:
  void start() {
    end_   = time_point{};
    start_ = ClockT::now();
  }

  void stop() { end_ = ClockT::now(); }

  auto duration() const {
    assert(end_ != time_point{} && "stop the gTimer first");
    return std::chrono::duration<double>(end_ - start_);
  }
};

extern Timer<> g_timer;

}  // namespace helper
}  // namespace solver

#endif  // FG_SOLVER_HELPER_H_