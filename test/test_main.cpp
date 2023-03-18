/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-17 22:32:33
 * @modify date 2023-03-17 22:32:33
 * @desc main test entry
 */
// gtest
#include <gtest/gtest.h>
// local
#include "dfpn_test.h"
#include "minimax_test.h"

int main(int argc, char **argv) {
  // https://stackoverflow.com/questions/12076072/how-to-run-specific-test-cases-in-googletest
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::GTEST_FLAG(filter) = "DFPN_*:*MINIMAX_SIMPLE*:*MINIMAX_LARGE*";
  return RUN_ALL_TESTS();
}
