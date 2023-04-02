/**
 * @author      Yanqing Wu, Junwen Shen, Luke Kapeluck
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:29:55
 * @modify date 2023-04-01 20:26:47
 * @desc Game class,responsible for play, find possible_moves
 */
#ifndef FG_SOLVER_GAME_H_
#define FG_SOLVER_GAME_H_
// std
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>
// local
#include "helper.h"

using solver::helper::PLAYER;
using solver::helper::Pos;

namespace solver {

class Game {
  typedef std::unordered_set<Pos, Pos::Hash> PosSet;

 public:
  explicit Game(const std::string &input);
  Game(const Game &other);
  // TODO: destructor of Game class

  friend std::ostream &operator<<(std::ostream &os, const Game &game);

  std::string toString() const;
  static bool isValidGameString(const std::string &game_string);
  void unsafePlay(const Pos &pos, uint8_t value);
  void undo(const Pos &pos);
  inline void changeToPlay();

  bool isValid();
  bool isTerminal();

  std::unordered_map<Pos, std::vector<uint8_t>, Pos::Hash> getPossibleMoves();

  inline PLAYER toPlay() const { return to_play_; }

 private:
  PLAYER to_play_;
  uint8_t width_ : 4;
  uint8_t height_ : 4;
  std::valarray<uint8_t> data_;

  std::vector<Pos> empty_positions_;
  std::vector<Pos> filled_positions_;

  std::unordered_map<Pos, std::vector<uint8_t>, Pos::Hash> possible_moves_;
  bool is_expanded_  = false;
  bool is_generated_ = false;

  uint8_t get(uint8_t row, uint8_t col) const;
  uint8_t get(const Pos &pos) const;
  void set(const Pos &pos, uint8_t value);
  void reset(const Pos &pos);

  void parseGameString(const std::string &game_string);
  void floodFill(const Pos &starting_pos, PosSet &filled_visited, PosSet &empty_visited) const;

  void generateAllPositions();
  std::vector<Pos> getNeighbours(const Pos &pos) const;
  std::vector<Pos> getEmptyPositions();
  std::vector<Pos> getFilledPositions();
};

// inline function declaration
inline void Game::changeToPlay() {
  to_play_ = (to_play_ == PLAYER::BLACK) ? PLAYER::WHITE : PLAYER::BLACK;
}

}  // namespace solver

#endif  // FG_SOLVER_GAME_H_