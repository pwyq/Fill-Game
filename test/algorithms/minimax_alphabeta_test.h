/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 00:44:38
 * @modify date 2023-04-03 01:56:38
 * @desc Minimax with Alpha-Beta pruning
 */

#ifndef FG_TEST_MINIMAX_ALPHABETA_H_
#define FG_TEST_MINIMAX_ALPHABETA_H_

// gtest
#include <gtest/gtest.h>
// local
#include "algorithm_test_cases.h"
#include "solver/game.h"
#include "solver/minimax.h"

using solver::Game;
using solver::minimax::Minimax;

namespace fgtest {

class MinimaxAlphaBetaTest : public testing::Test {
 protected:
  MinimaxAlphaBetaTest()          = default;
  virtual ~MinimaxAlphaBetaTest() = default;

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

solver::minimax::Minimax* MinimaxAlphaBetaTest::agent_ = nullptr;
////////////////////////////////////////////////////////////////////

TEST_F(MinimaxAlphaBetaTest, SIMPLE_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_4) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_5) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_6) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_7) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_8) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_9) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_10) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_11) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_12) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_13) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_14) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_15) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_16) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_17) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_18) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_19) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(MinimaxAlphaBetaTest, SIMPLE_20) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

///////////////////////////////////////////////////
///// MINIMAX_ALPHABETA_MEDIUM
///////////////////////////////////////////////////

TEST_F(MinimaxAlphaBetaTest, MEDIUM_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_MEDIUM[index].second);
}

TEST_F(MinimaxAlphaBetaTest, MEDIUM_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_MEDIUM[index].second);
}

TEST_F(MinimaxAlphaBetaTest, MEDIUM_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_MEDIUM[index].second);
}

TEST_F(MinimaxAlphaBetaTest, MEDIUM_4) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_MEDIUM[index].second);
}

TEST_F(MinimaxAlphaBetaTest, MEDIUM_5) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_MEDIUM[index].second);
}

TEST_F(MinimaxAlphaBetaTest, MEDIUM_6) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_MEDIUM[index].second);
}

TEST_F(MinimaxAlphaBetaTest, MEDIUM_7) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_MEDIUM[index].second);
}

///////////////////////////////////////////////////
///// MINIMAX_ALPHABETA_LARGE
///////////////////////////////////////////////////

TEST_F(MinimaxAlphaBetaTest, HARD_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_HARD[index].second);
}

TEST_F(MinimaxAlphaBetaTest, HARD_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_HARD[index].second);
}

TEST_F(MinimaxAlphaBetaTest, HARD_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new Minimax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_HARD[index].second);
}

}  // namespace fgtest

#endif  // FG_TEST_MINIMAX_ALPHABETA_H_
