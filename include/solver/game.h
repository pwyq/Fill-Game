/**
 * @author      Yanqing Wu, Junwen Shen, Luke Kapeluck
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:29:55
 * @modify date 2023-02-10 05:29:55
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

namespace solver {

class Game {
  typedef std::unordered_set<Pos, Pos::Hash> PosSet;

 public:
  PLAYER to_play_;

  explicit Game(const std::string &input);

  Game(const Game &other);

  std::string toString() const;

  friend std::ostream &operator<<(std::ostream &os, const Game &game);

  static bool isValidGameString(const std::string &game_string);

  void parseGameString(const std::string &game_string);

  void unsafePlay(const Pos &pos, uint8_t value);

  void undo(const Pos &pos);

  inline void changeToPlay();

  bool isValid() const;

  bool isTerminal();

  std::unordered_map<Pos, std::vector<uint8_t>, Pos::Hash> getPossibleMoves();

  uint8_t get(uint8_t row, uint8_t col) const;

  uint8_t get(const Pos &pos) const;

  void set(const Pos &pos, uint8_t value);

  void reset(const Pos &pos);

  std::vector<Pos> getNeighbours(const Pos &pos) const;

  std::vector<Pos> getEmptyPositions() const;

  std::vector<Pos> getFilledPositions() const;

 private:
  uint8_t width_ : 4;
  uint8_t height_ : 4;
  std::valarray<uint8_t> data_;

  std::unordered_map<Pos, std::vector<uint8_t>, Pos::Hash> possible_moves_;
  bool is_expanded_ = false;

  void floodFill(const Pos &starting_pos, PosSet &filled_visited,
                 PosSet &empty_visited) const;
};

// inline function declaration
inline void Game::changeToPlay() {
  to_play_ = (to_play_ == PLAYER::BLACK) ? PLAYER::WHITE : PLAYER::BLACK;
}

}  // namespace solver

#endif  // FG_SOLVER_GAME_H_