/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:38:30
 * @modify date 2023-04-03 01:17:06
 * @desc Unit tests for DFPN solver
 */
#ifndef FG_TEST_DFPN_H_
#define FG_TEST_DFPN_H_

// gtest
#include <gtest/gtest.h>
// local
#include "algorithm_test_cases.h"
#include "solver/dfpn.h"
#include "solver/game.h"
#include "solver/helper.h"

using solver::Game;
using solver::dfpn::DFPN;
using solver::helper::Move;

namespace fgtest {

class DFPNTest : public testing::Test {
 protected:
  DFPNTest()          = default;
  virtual ~DFPNTest() = default;

 public:
  // Some expensive resource shared by all tests.
  static solver::dfpn::DFPN* agent_;

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

solver::dfpn::DFPN* DFPNTest::agent_ = nullptr;
////////////////////////////////////////////////////////////////////

TEST_F(DFPNTest, SIMPLE_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_4) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_5) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_6) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_7) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_8) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_9) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_10) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_11) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_12) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_13) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_14) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_15) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_16) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_17) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_18) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_19) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

TEST_F(DFPNTest, SIMPLE_20) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_SIMPLE[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_SIMPLE[index].second);
}

///////////////////////////////////////////////////
///// DFPN_MEDIUM
///////////////////////////////////////////////////

TEST_F(DFPNTest, MEDIUM_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(DFPNTest, MEDIUM_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(DFPNTest, MEDIUM_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(DFPNTest, MEDIUM_4) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(DFPNTest, MEDIUM_5) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(DFPNTest, MEDIUM_6) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

TEST_F(DFPNTest, MEDIUM_7) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_MEDIUM[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_MEDIUM[index].second);
}

///////////////////////////////////////////////////
///// DFPN_LARGE
///////////////////////////////////////////////////

TEST_F(DFPNTest, HARD_1) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_HARD[index].second);
}

TEST_F(DFPNTest, HARD_2) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_HARD[index].second);
}

TEST_F(DFPNTest, HARD_3) {
  unsigned short index = getIndexFromName(::testing::UnitTest::GetInstance()->current_test_info()->name());
  Game game(SHARED_HARD[index].first);
  agent_ = new DFPN(game);
  agent_->solve();
  EXPECT_EQ(agent_->getResult(), SHARED_HARD[index].second);
}

///////////////////////////////////////////////////
///// Winning moves
///////////////////////////////////////////////////

TEST_F(DFPNTest, MOVE_1) {
  Game game(".*.*.");
  agent_ = new DFPN(game);
  agent_->solve();

  Move ans1{{1, 0}, 1};
  Move ans2{{1, 0}, 2};
  Move agent_ans = agent_->bestMove();
  EXPECT_TRUE(agent_ans == ans1 || agent_ans == ans2)
      << "Where real value: " << agent_ans.toString()
      << " not equal neither: " << ans1.toString()
      << " nor: " << ans2.toString() << ".";
}

TEST_F(DFPNTest, MOVE_2) {
  Game game("...");
  agent_ = new DFPN(game);
  agent_->solve();

  Move ans1{{0, 1}, 1};
  Move ans2{{0, 1}, 2};
  Move agent_ans = agent_->bestMove();
  EXPECT_TRUE(agent_ans == ans1 || agent_ans == ans2)
      << "Where real value: " << agent_ans.toString()
      << " not equal neither: " << ans1.toString()
      << " nor: " << ans2.toString() << ".";
}

TEST_F(DFPNTest, MOVE_3) {
  Game game("1");
  agent_ = new DFPN(game);
  agent_->solve();

  Move ans{{0, 0}, 0};
  EXPECT_EQ(agent_->bestMove(), ans);
}

}  // namespace fgtest

#endif  //FG_TEST_DFPN_H_