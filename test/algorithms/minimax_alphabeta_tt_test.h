/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 00:44:38
 * @modify date 2023-04-03 01:59:53
 * @desc Minimax with Alpha-Beta pruning
 */

#ifndef FG_TEST_MINIMAX_ALPHABETA_TT_H_
#define FG_TEST_MINIMAX_ALPHABETA_TT_H_

// gtest
#include <gtest/gtest.h>
// local
#include "algorithm_test_cases.h"
#include "solver/game.h"
#include "solver/helper.h"
#include "solver/minimax.h"

using solver::Game;
using solver::helper::Move;
using solver::minimax::Minimax;

namespace fgtest {

class MinimaxAlphaBetaTTTest : public testing::Test {
 protected:
  MinimaxAlphaBetaTTTest()          = default;
  virtual ~MinimaxAlphaBetaTTTest() = default;

 public:
  // Some expensive resource shared by all tests.
  static solver::minimax::Minimax* agent_;

  static void SetUpTestSuite() {
    agent_ = nullptr;
  }

  static void TearDownTestSuite() {
    delete agent_;
    agent_ = nullptr;
  }

  void SetUp() override {
    // ...
  }

  void TearDown() override {
    delete agent_;
    agent_ = nullptr;
  }
};

solver::minimax::Minimax* MinimaxAlphaBetaTTTest::agent_ = nullptr;
////////////////////////////////////////////////////////////////////

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_4) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_5) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_6) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_7) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_8) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_9) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_10) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_11) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_12) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_13) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_14) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_15) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_16) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_17) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_18) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_19) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, SIMPLE_20) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

///////////////////////////////////////////////////
///// MINIMAX_ALPHABETA_TT_MEDIUM
///////////////////////////////////////////////////

TEST_F(MinimaxAlphaBetaTTTest, MEDIUM_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_MEDIUM[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, MEDIUM_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_MEDIUM[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, MEDIUM_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_MEDIUM[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, MEDIUM_4) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_MEDIUM[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, MEDIUM_5) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_MEDIUM[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, MEDIUM_6) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_MEDIUM[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, MEDIUM_7) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_MEDIUM[index].second);
}

///////////////////////////////////////////////////
///// MINIMAX_ALPHABETA_TT_LARGE
///////////////////////////////////////////////////

TEST_F(MinimaxAlphaBetaTTTest, HARD_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_HARD[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, HARD_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_HARD[index].second);
}

TEST_F(MinimaxAlphaBetaTTTest, HARD_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_HARD[index].second);
}

///////////////////////////////////////////////////
///// Winning moves
///////////////////////////////////////////////////

TEST_F(MinimaxAlphaBetaTTTest, MOVE_1) {
  Game game(".*.*.");
  agent_ = new Minimax(game);
  agent_->getAlphaBetaTranspositionTableResult();

  Move ans1{{1, 0}, 1};
  Move ans2{{1, 0}, 2};
  Move agent_ans = agent_->bestMove();
  EXPECT_TRUE(agent_ans == ans1 || agent_ans == ans2)
      << "Where real value: " << agent_ans.toString()
      << " not equal neither: " << ans1.toString()
      << " nor: " << ans2.toString() << ".";
}

TEST_F(MinimaxAlphaBetaTTTest, MOVE_2) {
  Game game("...");
  agent_ = new Minimax(game);
  agent_->getAlphaBetaTranspositionTableResult();

  Move ans1{{0, 1}, 1};
  Move ans2{{0, 1}, 2};
  Move agent_ans = agent_->bestMove();
  EXPECT_TRUE(agent_ans == ans1 || agent_ans == ans2)
      << "Where real value: " << agent_ans.toString()
      << " not equal neither: " << ans1.toString()
      << " nor: " << ans2.toString() << ".";
}

TEST_F(MinimaxAlphaBetaTTTest, MOVE_3) {
  Game game("1");
  agent_ = new Minimax(game);
  agent_->getAlphaBetaTranspositionTableResult();

  Move ans{{0, 0}, 0};
  EXPECT_EQ(agent_->bestMove(), ans);
}

}  // namespace fgtest

#endif  // FG_TEST_MINIMAX_ALPHABETA_TT_H_
