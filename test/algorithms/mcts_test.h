/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-04-04 15:56:37
 * @modify date 2023-04-04 16:02:49
 * @desc Unit tests for MCTS
 */
#ifndef FG_TEST_MCTS_H_
#define FG_TEST_MCTS_H_

// gtest
#include <gtest/gtest.h>
// local
#include "solver/game.h"
#include "solver/helper.h"
#include "solver/mcts.h"

using solver::Game;
using solver::helper::Move;
using solver::mcts::MCTS;

namespace fgtest {

class MCTSTest : public testing::Test {
 protected:
  MCTSTest()          = default;
  virtual ~MCTSTest() = default;

 public:
  // Some expensive resource shared by all tests.
  static solver::mcts::MCTS* agent_;

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

solver::mcts::MCTS* MCTSTest::agent_ = nullptr;
////////////////////////////////////////////////////////////////////

/**
 * MCTS is a search algorithm, it's not a solver;
 * So we cannot test it against the result of the game.
 * 
 * For now, we are testing MCTS against small scenarios.
 * 
 */

TEST_F(MCTSTest, MOVE_1) {
  Game game("13*.3");
  agent_ = new MCTS(game);
  agent_->search();

  Move ans{{1, 0}, 3};
  EXPECT_EQ(agent_->bestMove(), ans);
}

TEST_F(MCTSTest, MOVE_2) {
  Game game("1.*33");
  agent_ = new MCTS(game);
  agent_->search();

  Move ans{{0, 1}, 3};
  EXPECT_EQ(agent_->bestMove(), ans);
}

TEST_F(MCTSTest, MOVE_3) {
  Game game("1.*.2");
  agent_ = new MCTS(game);
  agent_->search();

  Move ans1{{0, 1}, 2};
  Move ans2{{1, 0}, 2};
  Move agent_ans = agent_->bestMove();
  EXPECT_TRUE(agent_ans == ans1 || agent_ans == ans2)
      << "Where real value: " << agent_ans.toString()
      << " not equal neither: " << ans1.toString()
      << " nor: " << ans2.toString() << ".";
}

TEST_F(MCTSTest, MOVE_4) {
  Game game("12*..");
  agent_ = new MCTS(game);
  agent_->search();

  Move ans1{{1, 1}, 2};
  Move ans2{{1, 0}, 2};
  Move agent_ans = agent_->bestMove();
  EXPECT_TRUE(agent_ans == ans1 || agent_ans == ans2)
      << "Where real value: " << agent_ans.toString()
      << " not equal neither: " << ans1.toString()
      << " nor: " << ans2.toString() << ".";
}

TEST_F(MCTSTest, MOVE_5) {
  Game game("1.*2.");
  agent_ = new MCTS(game);
  agent_->search();

  Move ans1{{1, 1}, 2};
  Move ans2{{0, 1}, 2};
  Move agent_ans = agent_->bestMove();
  EXPECT_TRUE(agent_ans == ans1 || agent_ans == ans2)
      << "Where real value: " << agent_ans.toString()
      << " not equal neither: " << ans1.toString()
      << " nor: " << ans2.toString() << ".";
}

TEST_F(MCTSTest, MOVE_6) {
  Game game(".");
  agent_ = new MCTS(game);
  agent_->search();

  Move ans{{0, 0}, 1};
  EXPECT_EQ(agent_->bestMove(), ans);
}

TEST_F(MCTSTest, MOVE_7) {
  Game game("1");
  agent_ = new MCTS(game);
  agent_->search();

  Move ans{{0, 0}, 0};
  EXPECT_EQ(agent_->bestMove(), ans);
}

TEST_F(MCTSTest, MOVE_8) {
  Game game(".*.*.");
  agent_ = new MCTS(game);
  agent_->search();

  Move ans1{{1, 0}, 1};
  Move ans2{{1, 0}, 2};
  Move agent_ans = agent_->bestMove();
  EXPECT_TRUE(agent_ans == ans1 || agent_ans == ans2)
      << "Where real value: " << agent_ans.toString()
      << " not equal neither: " << ans1.toString()
      << " nor: " << ans2.toString() << ".";
}

TEST_F(MCTSTest, MOVE_9) {
  Game game("...");
  agent_ = new MCTS(game);
  agent_->search();

  Move ans1{{0, 1}, 1};
  Move ans2{{0, 1}, 2};
  Move agent_ans = agent_->bestMove();
  EXPECT_TRUE(agent_ans == ans1 || agent_ans == ans2)
      << "Where real value: " << agent_ans.toString()
      << " not equal neither: " << ans1.toString()
      << " nor: " << ans2.toString() << ".";
}

}  // namespace fgtest

#endif  //FG_TEST_MCTS_H_
