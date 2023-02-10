/**
 * @author      Yanqing Wu, Junwen Shen, Luke Kapeluck
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:34:37
 * @modify date 2023-02-10 05:34:37
 */
#include "solver/game.h"
// std
#include <iostream>
#include <ostream>
#include <stdexcept>

namespace solver {

Game::Game(const std::string &input)
    : to_play_(PLAYER::BLACK), width_(0), height_(0), is_expanded_(false) {
  // std::cout << input;
  parseGameString(input);
}

Game::Game(const Game &other)
    : to_play_(other.to_play_),
      width_(other.width_),
      height_(other.height_),
      is_expanded_(false) {
  data_ = other.data_;
}

void Game::unsafePlay(const Pos &pos, uint8_t value) {
  if (get(pos) > 0) {
    // std::cout << this->toString() << std::endl;
    std::string reason = "Cannot play at " + pos.toString() + " with value " +
                         std::to_string((unsigned int)value) +
                         ", which is already filled." +
                         " Full game = " + this->toString();
    throw std::invalid_argument(reason);
  }
  set(pos, value);
  changeToPlay();
}

void Game::undo(const Pos &pos) {
  reset(pos);
  changeToPlay();
}

void Game::floodFill(const Pos &starting_pos, PosSet &filled_visited,
                     PosSet &empty_visited) const {  // NOLINT
  filled_visited.insert(starting_pos);
  uint8_t value = get(starting_pos);
  for (auto neighbour : getNeighbours(starting_pos)) {
    uint8_t neighbour_value = get(neighbour);
    if (neighbour_value == 0) {
      // It's empty, add it to the set of liberties we saw
      empty_visited.insert(neighbour);
    } else if (neighbour_value == value) {
      // It's in our group
      if (filled_visited.find(neighbour) == filled_visited.end()) {
        // We haven't been there yet, go there
        floodFill(neighbour, filled_visited, empty_visited);
      }
    }
  }
}

bool Game::isValid() const {
  PosSet examined;
  for (auto pos : getFilledPositions()) {
    if (examined.find(pos) != examined.end()) {
      continue;
    }
    uint8_t value = get(pos);
    PosSet filled_visited;
    PosSet empty_visited;
    floodFill(pos, filled_visited, empty_visited);
    size_t num_in_group = filled_visited.size();
    if (num_in_group > value) {
      // We made a group that's too large
      return false;
    }

    size_t num_liberties = empty_visited.size();
    if (num_liberties == 0 && num_in_group < value) {
      // We surrounded the group and it's too small
      return false;
    }
    // For each of the ones we already discovered in the flood fill, remember we
    // were there already We don't need to examine them again
    for (auto it : filled_visited) {
      examined.insert(it);
    }
  }
  return true;
}

/**
void Game::play(const Pos &pos, uint8_t value) {
    unsafePlay(pos, value);
    if (!isValid()) {
        reset(pos);
        throw std::invalid_argument("Invalid move");
    }
}
**/

bool Game::isTerminal() { return getPossibleMoves().empty(); }

std::unordered_map<Pos, std::vector<uint8_t>, Pos::Hash>
Game::getPossibleMoves() {
  if (!is_expanded_ && possible_moves_.empty()) {
    is_expanded_ = true;
    if (width_ == 1 && height_ == 1 && get(0, 0) == 0) {
      possible_moves_[Pos{0, 0}] = {1};
      return possible_moves_;
    }
    PosSet examined;
    std::vector<Pos> empty_positions = getEmptyPositions();
    for (auto pos : empty_positions) {
      uint8_t counts[4] = {0};
      uint8_t num_liberties = 0;
      for (Pos neighbor : getNeighbours(pos)) {
        uint8_t neighbor_value = get(neighbor);
        if (neighbor_value > 0) {
          ++counts[neighbor_value - 1];
        } else {
          ++num_liberties;
        }
      }
      std::vector<uint8_t> values;
      for (uint8_t n = 1; n <= 4; ++n) {
        if (counts[n - 1] < n) {
          // There's not too many 1s,2s,3s, or 4s
          if (num_liberties == 0 && n != 1 && counts[n - 1] == 0) {
            // This is basically the equivalent of a suicide
            // No liberties, no friends, and not a 1
            continue;
          }
          // Good to try the board to see if it's valid
          unsafePlay(pos, n);
          if (isValid()) {
            values.push_back(n);
          }
          undo(pos);
        }
      }
      if (!values.empty()) {
        possible_moves_[pos] = values;
      }
      examined.insert(pos);
      if (!pos.is_important) {
        if (examined.find(pos) == examined.end()) {
          // We haven't explored this node already
          // It's an unimportant position, it can have every possibility
          possible_moves_[pos] = {1, 2, 3, 4};
        }
      }
    }
  }
  return possible_moves_;
}

bool Game::isValidGameString(const std::string &game_string) {
  uint8_t last_row_length = UINT8_MAX;
  uint8_t last_num_chars = 0;
  for (auto c : game_string) {
    if (c != '1' && c != '2' && c != '3' && c != '4' && c != '.' && c != '*') {
      return false;
    }
    if (c == '*') {
      if (last_row_length == UINT8_MAX) {
        last_row_length = (int8_t)last_num_chars;
      } else if (last_row_length != last_num_chars) {
        return false;
      }
      last_num_chars = 0;
    } else {
      ++last_num_chars;
    }
  }
  return !(last_row_length != last_num_chars && last_row_length != UINT8_MAX);
}

void Game::parseGameString(const std::string &game_string) {
  if (!isValidGameString(game_string)) {
    throw std::invalid_argument("Invalid game string");
  }
  bool width_found = false;
  width_ = 0;
  height_ = 1;
  for (char c : game_string) {
    if (c == '*') {
      ++height_;
      width_found = true;
    } else if (!width_found) {
      ++width_;
    }
  }
  data_ = std::valarray<uint8_t>((uint8_t)0, width_ * height_);
  uint8_t row = 0;
  uint8_t col = 0;
  for (char c : game_string) {
    if (c == '*') {
      ++row;
      col = 0;
    } else if (c != '.') {
      data_[row * width_ + col] = c - '0';
      changeToPlay();
      ++col;
    } else {
      ++col;
    }
  }
}

std::ostream &operator<<(std::ostream &os, const Game &game) {
  for (uint8_t row = 0; row < game.height_; ++row) {
    for (uint8_t col = 0; col < game.width_; ++col) {
      uint8_t value = game.get(row, col);
      if (value != 0) {
        os << (size_t)value << " ";
      } else {
        os << ". ";
      }
    }
    os << std::endl;
  }
  return os;
}

uint8_t Game::get(uint8_t row, uint8_t col) const {
  return data_[row * width_ + col];
}

uint8_t Game::get(const Pos &pos) const {
  return data_[pos.row * width_ + pos.col];
}

void Game::set(const Pos &pos, uint8_t value) {
  data_[pos.row * width_ + pos.col] = value;
}

void Game::reset(const Pos &pos) { data_[pos.row * width_ + pos.col] = 0; }

std::vector<Pos> Game::getNeighbours(const Pos &pos) const {
  uint8_t row = pos.row;
  uint8_t col = pos.col;
  std::vector<Pos> ret;
  if (row > 0) {
    ret.push_back(Pos{(uint8_t)(row - 1), col});
  }
  if (row < height_ - 1) {
    ret.push_back(Pos{(uint8_t)(row + 1), col});
  }
  if (col > 0) {
    ret.push_back(Pos{row, (uint8_t)(col - 1)});
  }
  if (col < width_ - 1) {
    ret.push_back(Pos{row, (uint8_t)(col + 1)});
  }
  return ret;
}

std::vector<Pos> Game::getEmptyPositions() const {
  std::vector<Pos> ret;
  for (uint8_t row = 0; row < height_; ++row) {
    for (uint8_t col = 0; col < width_; ++col) {
      if (get(row, col) == 0) {
        Pos p = Pos{row, col};
        for (auto neighbour : getNeighbours(p)) {
          if (get(neighbour) > 0) {
            p.is_important = true;
            break;
          }
        }
        ret.push_back(Pos{row, col});
      }
    }
  }
  return ret;
}

std::vector<Pos> Game::getFilledPositions() const {
  std::vector<Pos> ret;
  for (uint8_t row = 0; row < height_; ++row) {
    for (uint8_t col = 0; col < width_; ++col) {
      if (get(row, col) != 0) {
        ret.push_back(Pos{row, col});
      }
    }
  }
  return ret;
}

std::string Game::toString() const {
  std::string ret;
  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      uint8_t value = get(row, col);
      if (value != 0) {
        ret += std::to_string(value);
      } else {
        ret += ".";
      }
    }
    ret += "*";
  }
  ret.pop_back();
  return ret;
}

}  // namespace solver