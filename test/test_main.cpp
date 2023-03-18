/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-17 22:32:33
 * @modify date 2023-03-18 00:44:28
 * @desc main test entry
 */
// gtest
#include <gtest/gtest.h>
// local
#include "dfpn_test.h"
#include "minimax_alphabeta_test.h"
#include "minimax_test.h"
#include "negamax_alphabeta_test.h"
#include "negamax_alphabeta_tt_test.h"
#include "negamax_test.h"

int main(int argc, char **argv) {
  // https://stackoverflow.com/questions/12076072/how-to-run-specific-test-cases-in-googletest
  ::testing::InitGoogleTest(&argc, argv);
  // Minimax and Negamax is slow on MEDIUM 5 and 9
  ::testing::GTEST_FLAG(filter) =
      "DFPN_*:"
      // "*MINIMAX_SIMPLE*:"
      // "*MINIMAX_LARGE*:"
      // "*MINIMAX_ALPHABETA_*:"
      // "*NEGAMAX_SIMPLE*:"
      // "*NEGAMAX_LARGE*:"
      "*NEGAMAX_ALPHABETA_*:"
      "*NEGAMAX_ALPHABETA_TT_*:";
  return RUN_ALL_TESTS();
}
