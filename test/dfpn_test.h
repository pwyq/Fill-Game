/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:38:30
 * @modify date 2023-02-10 05:38:30
 * @desc Unit tests for DFPN solver
 */
// gtest
#include <gtest/gtest.h>
// local
#include "dfpn.h"
#include "game.h"

namespace solver {
namespace dfpn {

/**
 * @brief We are testing against the WIN/LOSS/UNKNOWN result.
 * With result=WIN, we are also testing against the winning move (only for
 * certain cases).
 *
 * Simple test: board less than and equal to 3x3,
 * Midium test: board size between 4x4 and 7x7,
 * Large  test: board size between 8x8 and 10x10; or too many empty cells
 */
TEST(DFPN_SIMPLE, 1) {
  std::string game_string = "1.*.3";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'L');
}

TEST(DFPN_SIMPLE, 2) {
  std::string game_string = "13*.3";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult().substr(0, 7), "W 0 1 3");
}

TEST(DFPN_SIMPLE, 3) {
  std::string game_string = "1.*33";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult().substr(0, 7), "W 1 0 3");
}

TEST(DFPN_SIMPLE, 4) {
  std::string game_string = "1.*.2";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'W');
}

TEST(DFPN_SIMPLE, 5) {
  std::string game_string = "1..*.2.";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'W');
}

TEST(DFPN_SIMPLE, 6) {
  std::string game_string = "1..*.2.*2..";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'W');
}

TEST(DFPN_SIMPLE, 7) {
  std::string game_string = "1..*.2.*1..";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'W');
}

TEST(DFPN_SIMPLE, 8) {
  std::string game_string = ".33*.23*121";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'W');
}

TEST(DFPN_SIMPLE, 9) {
  std::string game_string = ".";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult().substr(0, 7), "W 0 0 1");
}

TEST(DFPN_SIMPLE, 10) {
  std::string game_string = ".*.*.";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'W');
}

TEST(DFPN_SIMPLE, 11) {
  std::string game_string = "...";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'W');
}

TEST(DFPN_SIMPLE, 12) {
  std::string game_string = "1.1*...*1.1";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'W');
}

TEST(DFPN_SIMPLE, 13) {
  std::string game_string = "3.3*.3.";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'L');
}

TEST(DFPN_SIMPLE, 14) {
  std::string game_string = ".33";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult().substr(0, 7), "W 0 0 3");
}

TEST(DFPN_SIMPLE, 15) {
  std::string game_string = ".2";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult().substr(0, 7), "W 0 0 2");
}

TEST(DFPN_SIMPLE, 16) {
  std::string game_string = "144*3.4*134";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult().substr(0, 7), "W 1 1 3");
}

TEST(DFPN_SIMPLE, 17) {
  std::string game_string = "131*4.2*141";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'L');
}

///////////////////////////////////////////////////
///// DFPN_MEDIUM
///////////////////////////////////////////////////

TEST(DFPN_MEDIUM, 3) {
  std::string game_string = "..4.*44.4*..4.";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'W');
}

TEST(DFPN_MEDIUM, 4) {
  std::string game_string = "2241*44.4*2241";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'L');
}

TEST(DFPN_MEDIUM, 5) {
  // W 1 1 2 ~ 38393
  std::string game_string = "1...*2...*..43";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'W');
}

TEST(DFPN_MEDIUM, 6) {
  // W 3 0 3 ~ 4512
  std::string game_string = "1...*2...";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'W');
}

TEST(DFPN_MEDIUM, 7) {
  // W 2 2 1 ~ 16
  std::string game_string = "33213*2..33*44.22*33314*2244.";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'W');
}

TEST(DFPN_MEDIUM, 8) {
  // W 2 0 2 ~ 533
  std::string game_string = "33..3*2..33*44.22*33314*2244.";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'W');
}

TEST(DFPN_MEDIUM, 9) {
  // W 1 1 3 ~ 504073
  std::string game_string = "..*1.*..*22*..*..";
  Game game(game_string);
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'W');
}

///////////////////////////////////////////////////
///// DFPN_LARGE
///////////////////////////////////////////////////

/**
TEST(DFPN_LARGE, 1) {
    std::string game_string = ".....*.....*.....*.....";
    Game game(game_string);
    DFPN dfpn(game);
    dfpn.solve();
    EXPECT_EQ(dfpn.formatResult()[0], '?');
}

TEST(DFPN_LARGE, 2) {
    std::string game_string = ".....*..2..*.2...*.....*.....";
    Game game(game_string);
    DFPN dfpn(game);
    dfpn.solve();
    EXPECT_EQ(dfpn.formatResult()[0], '?');
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

TEST(DFPN_LARGE, 3) {
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
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult()[0], 'L');
}

TEST(DFPN_LARGE, 4) {
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
  DFPN dfpn(game);
  dfpn.solve();
  EXPECT_EQ(dfpn.formatResult().substr(0, 7), "W 7 9 3");
}

}  // namespace dfpn
}  // namespace solver

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
