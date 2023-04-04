/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 22:43:39
 * @modify date 2023-04-03 02:07:43
 * @desc Proof Number Search
 */

#ifndef FG_TEST_PNS_H_
#define FG_TEST_PNS_H_

// gtest
#include <gtest/gtest.h>
// local
#include "algorithm_test_cases.h"
#include "solver/game.h"
#include "solver/helper.h"
#include "solver/pns.h"

using solver::Game;
using solver::helper::Move;
using solver::pns::PNS;

namespace fgtest {

class PNSTest : public testing::Test {
 protected:
  PNSTest()          = default;
  virtual ~PNSTest() = default;

 public:
  // Some expensive resource shared by all tests.
  static solver::pns::PNS* agent_;

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

solver::pns::PNS* PNSTest::agent_ = nullptr;
////////////////////////////////////////////////////////////////////

TEST_F(PNSTest, SIMPLE_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
};

TEST_F(PNSTest, SIMPLE_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_4) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_5) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_6) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_7) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_8) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_9) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_10) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_11) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_12) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_13) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_14) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_15) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_16) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_17) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_18) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_19) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(PNSTest, SIMPLE_20) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

///////////////////////////////////////////////////
///// PNS_MEDIUM
///////////////////////////////////////////////////

TEST_F(PNSTest, MEDIUM_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(PNSTest, MEDIUM_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(PNSTest, MEDIUM_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(PNSTest, MEDIUM_4) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(PNSTest, MEDIUM_5) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(PNSTest, MEDIUM_6) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(PNSTest, MEDIUM_7) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

///////////////////////////////////////////////////
///// PNS_HARD
///////////////////////////////////////////////////

TEST_F(PNSTest, HARD_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_HARD[index].second);
}

TEST_F(PNSTest, HARD_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_HARD[index].second);
}

TEST_F(PNSTest, HARD_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new PNS(game);
  EXPECT_EQ(agent_->getResult(), SHARED_HARD[index].second);
}

///////////////////////////////////////////////////
///// Winning moves
///////////////////////////////////////////////////

TEST_F(PNSTest, MOVE_1) {
  Game game(".*.*.");
  agent_ = new PNS(game);
  agent_->getResult();

  Move ans{{1, 0}, 1};
  EXPECT_EQ(agent_->bestMove(), ans);
}

TEST_F(PNSTest, MOVE_2) {
  Game game("...");
  agent_ = new PNS(game);
  agent_->getResult();

  Move ans{{0, 1}, 1};
  EXPECT_EQ(agent_->bestMove(), ans);
}

TEST_F(PNSTest, MOVE_3) {
  Game game("1");
  agent_ = new PNS(game);
  agent_->getResult();

  Move ans{{0, 0}, 0};
  EXPECT_EQ(agent_->bestMove(), ans);
}

}  // namespace fgtest

#endif  // FG_TEST_PNS_H_
