/**
 * @author      Yanqing Wu, Junwen Shen
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-04-01 23:25:48
 * @modify date 2023-04-01 23:25:48
 * @desc Test performance of 2D construction vs 1D construction
 */
// std
#include <chrono>
#include <iostream>
#include <string>
#include <valarray>
// local

#define TEST_NUM 1000000

// std
#if defined(_WIN32)
#include <psapi.h>
#include <windows.h>

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <sys/resource.h>
#include <unistd.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <mach/mach.h>

#elif (defined(_AIX) || defined(__TOS__AIX__)) || (defined(__sun__) || defined(__sun) || defined(sun) && (defined(__SVR4) || defined(__svr4__)))
#include <fcntl.h>
#include <procfs.h>

#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
#include <cstdio>

#endif

#else
#error "Cannot define getPeakRSS() or getCurrentRSS() for an unknown OS."
#endif

size_t getPeakRSS() {
#if defined(_WIN32)
  /* Windows -------------------------------------------------- */
  PROCESS_MEMORY_COUNTERS info;
  GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
  return (size_t)info.PeakWorkingSetSize;

#elif (defined(_AIX) || defined(__TOS__AIX__)) || (defined(__sun__) || defined(__sun) || defined(sun) && (defined(__SVR4) || defined(__svr4__)))
  /* AIX and Solaris ------------------------------------------ */
  struct psinfo psinfo;
  int fd = -1;
  if ((fd = open("/proc/self/psinfo", O_RDONLY)) == -1)
    return (size_t)0L; /* Can't open? */
  if (read(fd, &psinfo, sizeof(psinfo)) != sizeof(psinfo)) {
    close(fd);
    return (size_t)0L; /* Can't read? */
  }
  close(fd);
  return (size_t)(psinfo.pr_rssize * 1024L);

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
  /* BSD, Linux, and OSX -------------------------------------- */
  struct rusage rusage {};
  getrusage(RUSAGE_SELF, &rusage);
#if defined(__APPLE__) && defined(__MACH__)
  return (size_t)rusage.ru_maxrss;
#else
  return (size_t)(rusage.ru_maxrss * 1024L);
#endif

#else
  /* Unknown OS ----------------------------------------------- */
  return (size_t)0L; /* Unsupported. */
#endif
}

////////////////////////////////////////

class TwoD {
 public:
  explicit TwoD(const std::string& game_string);
  inline uint8_t get(uint8_t row, uint8_t col) { return game_[row][col]; }
  void set(uint8_t row, uint8_t col, uint8_t val);

 private:
  uint8_t row_;
  uint8_t col_;
  std::valarray<std::valarray<uint8_t>> game_;
};

TwoD::TwoD(const std::string& game_string) {
  // Count the width and height
  bool width_found    = false;
  size_t width_count  = 0;
  size_t height_count = 1;
  for (char c : game_string) {
    if (c == '*') {
      ++height_count;
      width_found = true;
    } else if (width_found == false) {
      ++width_count;
    }
  }
  // Create the board
  row_  = width_count;
  col_  = height_count;
  game_ = std::valarray<std::valarray<uint8_t>>(std::valarray<uint8_t>(col_), row_);

  // Fill the board in
  size_t r = 0;
  size_t c = 0;
  for (char ch : game_string) {
    if (ch == '*') {
      ++r;
      c = 0;
    } else {
      if (ch == '.') {
        game_[r][c] = 0;
      } else {
        game_[r][c] = ch - '0';
      }
      ++c;
    }
  }
}

void TwoD::set(uint8_t row, uint8_t col, uint8_t val) {
  game_[row][col] = val;
}

////////////////////////////////////////

class OneD {
 public:
  explicit OneD(const std::string& game_string);
  inline uint8_t get(uint8_t row, uint8_t col) { return game_[row * col_ + col]; }
  void set(uint8_t row, uint8_t col, uint8_t val);

 private:
  uint8_t row_ = 9;
  uint8_t col_ = 9;
  std::valarray<uint8_t> game_;
};

OneD::OneD(const std::string& game_string) {
  game_       = std::valarray<uint8_t>((uint8_t)0, row_ * col_);
  uint8_t row = 0;
  uint8_t col = 0;
  for (char c : game_string) {
    if (c == '*') {
      ++row;
      col = 0;
    } else if (c != '.') {
      game_[row * col_ + col] = c - '0';
      ++col;
    } else {
      ++col;
    }
  }
}

void OneD::set(uint8_t row, uint8_t col, uint8_t val) {
  game_[row * col_ + col] = val;
}

////////////////////

int main() {
  std::string game_string = "123456789*123456789*123456789*123456789*123456789*123456789*123456789*123456789*123456789";

  ////////////////////////// 2D

#if false

  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  for (int i = 0; i < TEST_NUM; i++) {
    TwoD* my2d = new TwoD(game_string);
  }
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout << "[2D CREATE] Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[mus]" << std::endl;
  auto peakRSS = getPeakRSS();
  std::cout << "Peak RSS: " << peakRSS << std::endl;

  std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();

  TwoD* my2d = new TwoD(game_string);
  for (int i = 0; i < TEST_NUM; i++) {
    my2d->get(0, 0);  // BUG: seg fault? I init'ed it?
    my2d->get(5, 5);
    my2d->get(8, 8);
  }
  std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
  std::cout << "[2D GET] Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << "[mus]" << std::endl;
  peakRSS = getPeakRSS();
  std::cout << "Peak RSS: " << peakRSS << std::endl;

  std::chrono::steady_clock::time_point begin3 = std::chrono::steady_clock::now();

  my2d = new TwoD(game_string);
  for (int i = 0; i < TEST_NUM; i++) {
    my2d->set(0, 0, 3);
    my2d->set(5, 5, 3);
    my2d->set(8, 8, 3);
  }
  std::chrono::steady_clock::time_point end3 = std::chrono::steady_clock::now();
  std::cout << "[2D SET] Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3).count() << "[mus]" << std::endl;
  peakRSS = getPeakRSS();
  std::cout << "Peak RSS: " << peakRSS << std::endl;

#else
  ////////////////////////// 1D

  std::chrono::steady_clock::time_point begin4 = std::chrono::steady_clock::now();
  for (int i = 0; i < TEST_NUM; i++) {
    OneD* my1d = new OneD(game_string);
  }
  std::chrono::steady_clock::time_point end4 = std::chrono::steady_clock::now();
  std::cout << "[1D CREATE] Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end4 - begin4).count() << "[mus]" << std::endl;
  auto peakRSS = getPeakRSS();
  std::cout << "Peak RSS: " << peakRSS << std::endl;

  std::chrono::steady_clock::time_point begin5 = std::chrono::steady_clock::now();

  OneD* my1d = new OneD(game_string);
  for (int i = 0; i < TEST_NUM; i++) {
    my1d->get(0, 0);
    my1d->get(5, 5);
    my1d->get(8, 8);
  }
  std::chrono::steady_clock::time_point end5 = std::chrono::steady_clock::now();
  std::cout << "[1D GET] Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end5 - begin5).count() << "[mus]" << std::endl;
  peakRSS = getPeakRSS();
  std::cout << "Peak RSS: " << peakRSS << std::endl;

  std::chrono::steady_clock::time_point begin6 = std::chrono::steady_clock::now();

  my1d = new OneD(game_string);
  for (int i = 0; i < TEST_NUM; i++) {
    my1d->set(0, 0, 3);
    my1d->set(5, 5, 3);
    my1d->set(8, 8, 3);
  }
  std::chrono::steady_clock::time_point end6 = std::chrono::steady_clock::now();
  std::cout << "[1D SET] Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end6 - begin6).count() << "[mus]" << std::endl;
  peakRSS = getPeakRSS();
  std::cout << "Peak RSS: " << peakRSS << std::endl;

#endif

  return 0;
}
