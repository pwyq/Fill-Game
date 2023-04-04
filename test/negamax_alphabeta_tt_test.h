/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 13:40:42
 * @modify date 2023-04-03 02:05:36
 * @desc Negamax with Alpha-Beta pruning + Transposition Table
 */

#ifndef FG_TEST_NEGAMAX_ALPHABETA_TT_H_
#define FG_TEST_NEGAMAX_ALPHABETA_TT_H_

// gtest
#include <gtest/gtest.h>
// local
#include "algorithm_test_cases.h"
#include "game.h"
#include "negamax.h"

namespace solver::negamax {

class NegamaxAlphaBetaTTTest : public testing::Test {
 protected:
  NegamaxAlphaBetaTTTest()          = default;
  virtual ~NegamaxAlphaBetaTTTest() = default;

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

solver::negamax::Negamax* NegamaxAlphaBetaTTTest::agent_ = nullptr;
////////////////////////////////////////////////////////////////////

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
};

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_4) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_5) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_6) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_7) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_8) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_9) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_10) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_11) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_12) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_13) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_14) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_15) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_16) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, SIMPLE_17) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_SIMPLE[index].second);
}

///////////////////////////////////////////////////
///// NEGAMAX_ALPHABETA_TT_MEDIUM
///////////////////////////////////////////////////

TEST_F(NegamaxAlphaBetaTTTest, MEDIUM_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());

  // index = 0;  // same weird bug
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, MEDIUM_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, MEDIUM_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());

  // index = 2;  // same weird bug
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, MEDIUM_4) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, MEDIUM_5) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, MEDIUM_6) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, MEDIUM_7) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_MEDIUM[index].second);
}

///////////////////////////////////////////////////
///// NEGAMAX_ALPHABETA_TT_HARD
///////////////////////////////////////////////////

TEST_F(NegamaxAlphaBetaTTTest, HARD_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_HARD[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, HARD_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_HARD[index].second);
}

TEST_F(NegamaxAlphaBetaTTTest, HARD_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getAlphaBetaTranspositionTableResult(), SHARED_HARD[index].second);
}

}  // namespace solver::negamax

#endif  // FG_TEST_NEGAMAX_ALPHABETA_TT_H_
