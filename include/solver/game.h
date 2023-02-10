#ifndef FG_SOLVER_GAME_H_
#define FG_SOLVER_GAME_H_

#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

#include "helper.h"

namespace Solver {

class Game {
  typedef std::unordered_set<Pos, Pos::Hash> PosSet;

private:
  uint8_t width : 4;
  uint8_t height : 4;
  std::valarray<uint8_t> data;

  std::unordered_map<Pos, std::vector<uint8_t>, Pos::Hash> possible_moves;
  bool is_expanded = false;

  void floodFill(const Pos &starting_pos, PosSet &filled_visited,
                 PosSet &empty_visited) const;

public:
  PLAYER to_play;

  explicit Game(const std::string &input);

  Game(const Game &other);

  std::string toString() const;

  friend std::ostream &operator<<(std::ostream &os, const Game &game);

  static bool isValidGameString(const std::string &game_string);

  void parseGameString(const std::string &game_string);

  void unsafePlay(const Pos &pos, uint8_t value);

  void undo(const Pos &pos);

  void changeToPlay();

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
};

} // namespace Solver

#endif // FG_SOLVER_GAME_H_