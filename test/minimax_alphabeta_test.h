/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-18 00:44:38
 * @modify date 2023-03-18 11:15:49
 * @desc Minimax with Alpha-Beta pruning
 */

#ifndef FG_TEST_MINIMAX_ALPHABETA_H_
#define FG_TEST_MINIMAX_ALPHABETA_H_

// gtest
#include <gtest/gtest.h>
// local
#include "game.h"
#include "minimax.h"

namespace solver {
namespace minimax {

/**
 * @brief We are testing against the WIN/LOSS/UNKNOWN result.
 * With result=WIN, we are also testing against the winning move (only for
 * certain cases).
 *
 * Simple test: board less than and equal to 3x3,
 * Midium test: board size between 4x4 and 7x7,
 * Large  test: board size between 8x8 and 10x10; or too many empty cells
 */
TEST(MINIMAX_ALPHABETA_SIMPLE, 1) {
  std::string game_string = "1.*.3";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), -1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 2) {
  std::string game_string = "13*.3";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 3) {
  std::string game_string = "1.*33";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 4) {
  std::string game_string = "1.*.2";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 5) {
  std::string game_string = "1..*.2.";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 6) {
  std::string game_string = "1..*.2.*2..";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 7) {
  std::string game_string = "1..*.2.*1..";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 8) {
  std::string game_string = ".33*.23*121";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 9) {
  std::string game_string = ".";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 10) {
  std::string game_string = ".*.*.";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 11) {
  std::string game_string = "...";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 12) {
  std::string game_string = "1.1*...*1.1";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 13) {
  std::string game_string = "3.3*.3.";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), -1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 14) {
  std::string game_string = ".33";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 15) {
  std::string game_string = ".2";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 16) {
  std::string game_string = "144*3.4*134";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_SIMPLE, 17) {
  std::string game_string = "131*4.2*141";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), -1);
}

///////////////////////////////////////////////////
///// MINIMAX_ALPHABETA_MEDIUM
///////////////////////////////////////////////////

TEST(MINIMAX_ALPHABETA_MEDIUM, 3) {
  std::string game_string = "..4.*44.4*..4.";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_MEDIUM, 4) {
  std::string game_string = "2241*44.4*2241";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), -1);
}

TEST(MINIMAX_ALPHABETA_MEDIUM, 5) {
  // W 1 1 2 ~ 38393
  std::string game_string = "1...*2...*..43";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_MEDIUM, 6) {
  // W 3 0 3 ~ 4512
  std::string game_string = "1...*2...";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_MEDIUM, 7) {
  // W 2 2 1 ~ 16
  std::string game_string = "33213*2..33*44.22*33314*2244.";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_MEDIUM, 8) {
  // W 2 0 2 ~ 533
  std::string game_string = "33..3*2..33*44.22*33314*2244.";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

TEST(MINIMAX_ALPHABETA_MEDIUM, 9) {
  // W 1 1 3 ~ 504073
  std::string game_string = "..*1.*..*22*..*..";
  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

///////////////////////////////////////////////////
///// MINIMAX_ALPHABETA_LARGE
///////////////////////////////////////////////////

/**
TEST(MINIMAX_ALPHABETA_LARGE, 1) {
    std::string game_string = ".....*.....*.....*.....";
    Game game(game_string);
    Minimax agent(game);
  
    EXPECT_EQ(agent.getAlphaBetaResult(), '?');
}

TEST(MINIMAX_ALPHABETA_LARGE, 2) {
    std::string game_string = ".....*..2..*.2...*.....*.....";
    Game game(game_string);
    Minimax agent(game);
  
    EXPECT_EQ(agent.getAlphaBetaResult(), '?');
}
*/
/*
 * 1 2 2 3 3 3 4 4 4 4
 * 4 4 4 4 2 2 3 3 3 1
 * 1 2 2 3 3 3 4 4 4 4
 * 4 4 4 4 2 2 3 3 3 1
 * 1 2 2 3 3 3 4 4 4 4
 * 4 4 4 4 2 2 3 3 3 1
 * 1 2 2 3 3 3 4 4 4 4
 * 4 4 4 4 2 2 3 3 3 1
 * 1 2 2 3 3 3 4 4 4 4
 * 4 4 4 4 2 2 3 3 3 1
 *
 */

TEST(MINIMAX_ALPHABETA_LARGE, 3) {
  std::string game_string;
  game_string += "1223334444";
  game_string += "*4444223331";
  game_string += "*1223334444";
  game_string += "*4444223331";
  game_string += "*1223334444";
  game_string += "*4444223331";
  game_string += "*1223334444";
  game_string += "*44.4223331";
  game_string += "*1223334444";
  game_string += "*4444223.31";

  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), -1);
}

TEST(MINIMAX_ALPHABETA_LARGE, 4) {
  std::string game_string;
  game_string += "1223334444";
  game_string += "*4444223331";
  game_string += "*1223334444";
  game_string += "*4444223331";
  game_string += "*1223334444";
  game_string += "*4444223331";
  game_string += "*1223334444";
  game_string += "*4444223331";
  game_string += "*1223334444";
  game_string += "*4444223.31";

  Game game(game_string);
  Minimax agent(game);
  EXPECT_EQ(agent.getAlphaBetaResult(), 1);
}

}  // namespace minimax
}  // namespace solver

#endif  // FG_TEST_MINIMAX_ALPHABETA_H_