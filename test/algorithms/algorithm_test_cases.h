/**
 * @author      Yanqing Wu, Junwen Shen
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-04-02 22:32:23
 * @modify date 2023-04-03 23:31:20
 * @desc Sharing Test
 *
 * https://github.com/google/googletest/blob/main/docs/advanced.md#sharing-resources-between-tests-in-the-same-test-suite
 */

#ifndef FG_TEST_ALGORITHM_TEST_CASES_H_
#define FG_TEST_ALGORITHM_TEST_CASES_H_

// gtest
#include <gtest/gtest.h>
// std
#include <sstream>
#include <vector>
// local
#include "solver/game.h"

namespace fgtest {

/**
 * @brief We are testing against the WIN/LOSS/UNKNOWN result.
 * With result=WIN, we are also testing against the winning move (only for
 * certain cases).
 *
 * Simple test: board less than and equal to 3x3,
 * Midium test: board size between 4x4 and 7x7,
 * Large  test: board size between 8x8 and 10x10; or too many empty cells
 */

using TestContainer = std::vector<std::pair<std::string, short>>;

unsigned short getIndexFromName(const char* x) {
  std::stringstream s(x);
  char c = 0;
  while (c != '_') {
    s >> c;
  }
  unsigned short y;
  s >> y;
  // std::cout << x << std::endl;   // for the very weird bug in minimax-ab-tt and negamax-ab-tt medium.1 and medium.3
  // std::cout << y << " " << y - 1 << std::endl;
  return y - 1;
}

const TestContainer SHARED_SIMPLE = {
    // 1
    std::make_pair("1.*.3", -1),
    // 2
    std::make_pair("13*.3", 1),
    // 3
    std::make_pair("1.*33", 1),
    // 4
    std::make_pair("1.*.2", 1),
    // 5
    std::make_pair("1..*.2.", 1),
    // 6
    std::make_pair("1..*.2.*2..", 1),
    // 7
    std::make_pair("1..*.2.*1..", 1),
    // 8
    std::make_pair(".33*.23*121", 1),
    // 9
    std::make_pair(".", 1),
    // 10
    std::make_pair(".*.*.", 1),
    // 11
    std::make_pair("...", 1),
    // 12
    std::make_pair("1.1*...*1.1", 1),
    // 13
    std::make_pair("3.3*.3.", -1),
    // 14
    std::make_pair(".33", 1),
    // 15
    std::make_pair(".2", 1),
    // 16
    std::make_pair("144*3.4*134", 1),
    // 17
    std::make_pair("131*4.2*141", -1),
    // 18
    std::make_pair("1..*.1.*..1", -1),
    // 19
    std::make_pair("1.1.*.1.1*..1.*...1", -1),
    // 20
    std::make_pair("1", -1)

};  // end of TestContainer SHARED_SIMPLE

const TestContainer SHARED_MEDIUM = {
    // 1
    std::make_pair("..4.*44.4*..4.", 1),
    // 2
    std::make_pair("2241*44.4*2241", -1),
    // 3
    std::make_pair("1...*2...*..43", 1),
    // 4
    std::make_pair("1...*2...", 1),
    // 5
    std::make_pair("33213*2..33*44.22*33314*2244.", 1),
    // 6
    std::make_pair("33..3*2..33*44.22*33314*2244.", 1),
    // 7
    std::make_pair("..*1.*..*22*..*..", 1)

};  // end of TestContainer SHARED_MEDIUM

/*
 * 1 2 2 3 3 3 4 4 4 4
 * 4 4 4 4 2 2 3 3 3 1
 * 1 2 2 3 3 3 4 4 4 4
 * 4 4 4 4 2 2 3 3 3 1
 * 1 2 2 3 3 3 4 4 4 4
 * 4 4 4 4 2 2 3 3 3 1
 * 1 2 2 3 3 3 4 4 4 4
 * 4 4 4 4 2 2 3 3 3 1
 * 1 2 2 3 3 3 4 4 4 4
 * 4 4 4 4 2 2 3 3 3 1
 *
 */

const TestContainer SHARED_HARD = {
    // 1
    std::make_pair("\
1223334444*\
4444223331*\
1223334444*\
4444223331*\
1223334444*\
4444223331*\
1223334444*\
44.4223331*\
1223334444*\
4444223.31",
                   -1),
    // 2
    std::make_pair("\
1223334444*\
4444223331*\
1223334444*\
4444223331*\
1223334444*\
4444223331*\
1223334444*\
4444223331*\
1223334444*\
4444223.31",
                   1),
    // 3
    std::make_pair("\
1223334444*\
444422.331*\
122.334444*\
4444223331*\
122333.444*\
4444223331*\
1223334444*\
4444223.31*\
1223334444*\
4444223.31",
                   1)

};  // end of TestContainer SHARED_HARD

TEST(VALID_ALGO_TEST_CASES, SIMPLE) {
  for (const auto& i : SHARED_SIMPLE) {
    EXPECT_EQ(true, solver::Game::isValidGameString(i.first));
  }
}

TEST(VALID_ALGO_TEST_CASES, MEDIUM) {
  for (const auto& i : SHARED_MEDIUM) {
    EXPECT_EQ(true, solver::Game::isValidGameString(i.first));
  }
}

TEST(VALID_ALGO_TEST_CASES, HARD) {
  for (const auto& i : SHARED_HARD) {
    EXPECT_EQ(true, solver::Game::isValidGameString(i.first));
  }
}

}  // namespace fgtest

#endif
