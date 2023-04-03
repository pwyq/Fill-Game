/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-17 22:32:33
 * @modify date 2023-04-03 02:15:46
 * @desc main test entry
 */
// gtest
#include <gtest/gtest.h>
// local
#include "dfpn_test.h"
#include "minimax_alphabeta_test.h"
#include "minimax_alphabeta_tt_test.h"
#include "minimax_test.h"
#include "negamax_alphabeta_test.h"
#include "negamax_alphabeta_tt_test.h"
#include "negamax_test.h"
#include "pns_test.h"

int main(int argc, char **argv) {
  // https://stackoverflow.com/questions/12076072/how-to-run-specific-test-cases-in-googletest
  ::testing::InitGoogleTest(&argc, argv);
  // Minimax and Negamax are slow on MEDIUM
  ::testing::GTEST_FLAG(filter) =
      "VALID_ALGO_TEST_CASES*:"
      "*DFPNTest*:"
      "*PNSTest*:"
      "*MinimaxTest.SIMPLE*:"
      "*MinimaxTest.HARD*:"
      "*MinimaxAlphaBetaTest*:"
      "*MinimaxAlphaBetaTTTest*:"
      "*NegamaxTest.SIMPLE*:"
      "*NegamaxTest.HARD*:"
      "*NegamaxAlphaBetaTest*:"
      "*NegamaxAlphaBetaTTTest*:";
  return RUN_ALL_TESTS();
}
