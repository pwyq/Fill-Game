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
#include "game.h"
#include "minimax.h"

namespace solver {
namespace minimax {

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
};

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

///////////////////////////////////////////////////
///// MINIMAX_ALPHABETA_TT_MEDIUM
///////////////////////////////////////////////////

TEST_F(MinimaxAlphaBetaTTTest, MEDIUM_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  // std::cout << "index = " << index << std::endl;
  index = 0;  // there is a very weird bug here, same name for other can be parsed correctly, this one looks correct, but got wrong result
  // MEDIUM_1
  // 0 -1
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
  // std::cout << "index = " << index << std::endl;
  index = 2;  // also the same weird bug (happens to nega-ab-tt as well)

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

}  // namespace minimax
}  // namespace solver

#endif  // FG_TEST_MINIMAX_ALPHABETA_TT_H_