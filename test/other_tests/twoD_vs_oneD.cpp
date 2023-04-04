/**
 * @author      Yanqing Wu, Junwen Shen
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-04-01 23:25:48
 * @modify date 2023-04-01 01:36:09
 * @desc Test performance of 2D construction vs 1D construction
 */
// std
#include <iostream>
#include <string>
#include <valarray>
// local
#include "solver/helper.h"

#define TEST_NUM 10000000

constexpr double MB = 1024 * 1024;

using solver::helper::getPeakRSS;
using solver::helper::Timer;
using solver::helper::toMilliseconds;

////////////////////////////////////////
class Board {
 public:
  virtual ~Board()                                        = default;
  virtual uint8_t get(uint8_t row, uint8_t col)           = 0;
  virtual void set(uint8_t row, uint8_t col, uint8_t val) = 0;

 protected:
  uint8_t row_;
  uint8_t col_;
};

class TwoD : public Board {
 public:
  explicit TwoD(const std::string& game_string);
  inline uint8_t get(uint8_t row, uint8_t col) override { return game_[row][col]; }
  void set(uint8_t row, uint8_t col, uint8_t val) override;

 private:
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
    } else if (!width_found) {
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

class OneD : public Board {
 public:
  explicit OneD(const std::string& game_string);
  inline uint8_t get(uint8_t row, uint8_t col) override { return game_[row * col_ + col]; }
  void set(uint8_t row, uint8_t col, uint8_t val) override;

 private:
  std::valarray<uint8_t> game_;
};

OneD::OneD(const std::string& game_string) {
  row_             = 0;
  col_             = 1;
  bool width_found = false;
  for (char c : game_string) {
    if (c == '*') {
      ++row_;
      width_found = true;
    } else if (!width_found) {
      ++col_;
    }
  }
  game_       = std::valarray<uint8_t>(game_string.size());
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

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: ./twoD_vs_oneD <1D>/<2D>" << std::endl;
    return 0;
  }
  std::string which(argv[1]);
  std::string game_string = "123456789*123456789*123456789*123456789*123456789*123456789*123456789*123456789*123456789";
  auto timer              = Timer();
  // Test initialization
  std::valarray<Board*> board_ptrs(TEST_NUM);
  if (which == "1D") {
    timer.start();
    for (int i = 0; i < TEST_NUM; i++) {
      board_ptrs[i] = new OneD(game_string);
    }
    timer.stop();
  } else {
    timer.start();
    for (int i = 0; i < TEST_NUM; i++) {
      board_ptrs[i] = new TwoD(game_string);
    }
    timer.stop();
  }
  std::cout << "Peak RSS: " << getPeakRSS() / MB << "MB" << std::endl;
  std::cout << "[" << which << " CREATE] Time: " << toMilliseconds(timer.duration()).count() << "ms" << std::endl;
  for (int i = 0; i < TEST_NUM; i++) {
    delete board_ptrs[i];
  }

  // Test get
  Board* b;
  if (which == "1D") {
    b = new OneD(game_string);
  } else {
    b = new TwoD(game_string);
  }
  timer.start();
  for (int i = 0; i < TEST_NUM; i++) {
    b->get(0, 0);
    b->get(5, 5);
    b->get(8, 8);
  }
  timer.stop();
  std::cout << "[" << which << " GET] Time: " << toMilliseconds(timer.duration()).count() << "ms" << std::endl;

  // Test set
  timer.start();
  for (int i = 0; i < TEST_NUM; i++) {
    b->set(0, 0, 1);
    b->set(5, 5, 1);
    b->set(8, 8, 1);
  }
  timer.stop();
  std::cout << "[" << which << " SET] Time: " << toMilliseconds(timer.duration()).count() << "ms" << std::endl;
  delete b;

  return 0;
}
