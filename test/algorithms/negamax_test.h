/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-17 22:25:21
 * @modify date 2023-04-03 02:02:09
 * @desc Unit tests for Negamax solver
 */
#ifndef FG_TEST_NEGAMAX_H_
#define FG_TEST_NEGAMAX_H_

// gtest
#include <gtest/gtest.h>
// local
#include "algorithm_test_cases.h"
#include "solver/game.h"
#include "solver/helper.h"
#include "solver/negamax.h"

using solver::Game;
using solver::helper::Move;
using solver::negamax::Negamax;

namespace fgtest {

class NegamaxTest : public testing::Test {
 protected:
  NegamaxTest()          = default;
  virtual ~NegamaxTest() = default;

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

solver::negamax::Negamax* NegamaxTest::agent_ = nullptr;
////////////////////////////////////////////////////////////////////

TEST_F(NegamaxTest, SIMPLE_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
};

TEST_F(NegamaxTest, SIMPLE_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_4) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_5) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_6) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_7) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_8) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_9) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_10) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_11) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_12) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_13) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_14) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_15) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_16) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_17) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_18) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_19) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(NegamaxTest, SIMPLE_20) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

///////////////////////////////////////////////////
///// NEGAMAX_MEDIUM
///////////////////////////////////////////////////

TEST_F(NegamaxTest, MEDIUM_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxTest, MEDIUM_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxTest, MEDIUM_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxTest, MEDIUM_4) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxTest, MEDIUM_5) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxTest, MEDIUM_6) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(NegamaxTest, MEDIUM_7) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

///////////////////////////////////////////////////
///// NEGAMAX_HARD
///////////////////////////////////////////////////

TEST_F(NegamaxTest, HARD_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_HARD[index].second);
}

TEST_F(NegamaxTest, HARD_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_HARD[index].second);
}

TEST_F(NegamaxTest, HARD_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new Negamax(game);
  EXPECT_EQ(agent_->getResult(), SHARED_HARD[index].second);
}

///////////////////////////////////////////////////
///// Winning moves
///////////////////////////////////////////////////

TEST_F(NegamaxTest, MOVE_1) {
  Game game(".*.*.");
  agent_ = new Negamax(game);
  agent_->getResult();

  Move ans{{1, 0}, 1};
  EXPECT_EQ(agent_->bestMove(), ans);
}

TEST_F(NegamaxTest, MOVE_2) {
  Game game("...");
  agent_ = new Negamax(game);
  agent_->getResult();

  Move ans{{0, 1}, 1};
  EXPECT_EQ(agent_->bestMove(), ans);
}

TEST_F(NegamaxTest, MOVE_3) {
  Game game("1");
  agent_ = new Negamax(game);
  agent_->getResult();

  Move ans{{0, 0}, 0};
  EXPECT_EQ(agent_->bestMove(), ans);
}

}  // namespace fgtest

#endif  // FG_TEST_NEGAMAX_H_
