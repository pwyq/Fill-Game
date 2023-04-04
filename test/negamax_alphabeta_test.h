/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 00:44:38
 * @modify date 2023-04-03 02:02:07
 * @desc Negamax with Alpha-Beta pruning
 */

#ifndef FG_TEST_NEGAMAX_ALPHABETA_H_
#define FG_TEST_NEGAMAX_ALPHABETA_H_

// gtest
#include <gtest/gtest.h>
// local
#include "algorithm_test_cases.h"
#include "solver/game.h"
#include "solver/negamax.h"

using solver::Game;
using solver::negamax::Negamax;

namespace fgtest {

class NegamaxAlphaBetaTest : public testing::Test {
 protected:
  NegamaxAlphaBetaTest()          = default;
  virtual ~NegamaxAlphaBetaTest() = default;

 public:
  // Some expensive resource shared by all tests.
  static solver::negamax::Negamax* agent_;

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

solver::negamax::Negamax* NegamaxAlphaBetaTest::agent_ = nullptr;
////////////////////////////////////////////////////////////////////

TEST_F(NegamaxAlphaBetaTest, SIMPLE_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
};

TEST_F(NegamaxAlphaBetaTest, SIMPLE_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTest, SIMPLE_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTest, SIMPLE_4) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTest, SIMPLE_5) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTest, SIMPLE_6) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTest, SIMPLE_7) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTest, SIMPLE_8) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTest, SIMPLE_9) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTest, SIMPLE_10) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTest, SIMPLE_11) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTest, SIMPLE_12) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTest, SIMPLE_13) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTest, SIMPLE_14) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTest, SIMPLE_15) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTest, SIMPLE_16) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTest, SIMPLE_17) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_SIMPLE[index].second);
}

///////////////////////////////////////////////////
///// NEGAMAX_ALPHABETA_MEDIUM
///////////////////////////////////////////////////

TEST_F(NegamaxAlphaBetaTest, MEDIUM_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxAlphaBetaTest, MEDIUM_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxAlphaBetaTest, MEDIUM_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxAlphaBetaTest, MEDIUM_4) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxAlphaBetaTest, MEDIUM_5) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxAlphaBetaTest, MEDIUM_6) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxAlphaBetaTest, MEDIUM_7) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_MEDIUM[index].second);
}

///////////////////////////////////////////////////
///// NEGAMAX_ALPHABETA_HARD
///////////////////////////////////////////////////

TEST_F(NegamaxAlphaBetaTest, HARD_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_HARD[index].second);
}

TEST_F(NegamaxAlphaBetaTest, HARD_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_HARD[index].second);
}

TEST_F(NegamaxAlphaBetaTest, HARD_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaResult(), SHARED_HARD[index].second);
}
}  // namespace fgtest

#endif  // FG_TEST_NEGAMAX_ALPHABETA_H_
