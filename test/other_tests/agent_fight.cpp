/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-04-03 21:34:32
 * @modify date 2023-04-03 23:43:55
 * @desc Test agents playing against each other
 * 
 * TODO: time constraint and memory constraint
 */

// std
#include <stdio.h>

#include <exception>
#include <iostream>
#include <string>
// local
#include "dfpn.h"
#include "game.h"
#include "helper.h"
#include "minimax.h"
#include "negamax.h"
#include "pns.h"

using std::cout;
using std::endl;

using solver::Game;
using solver::helper::Move;

using solver::dfpn::DFPN;
using solver::minimax::Minimax;
using solver::negamax::Negamax;
using solver::pns::PNS;

namespace test {

std::string generateBoardString(int board_size) {
  std::string res = "";
  for (int i = 0; i < board_size; i++) {
    res += std::string(board_size, '.');
    res += "*";
  }
  res.pop_back();
  return res;
}

constexpr uint32_t hash(const std::string_view data) noexcept {
  uint32_t hash = 5385;
  for (const auto& e : data) hash = ((hash << 5) + hash) + e;
  return hash;
}

Move getMove(std::string agent_name, Game game) {
  Move res_move;
  switch (hash(agent_name)) {
    case hash("pns"): {
      PNS* pns = new PNS(game);
      pns->getResult();
      res_move = pns->best_move();
      break;
    }
    case hash("dfpn"): {
      DFPN* dfpn = new DFPN(game);
      dfpn->solve();
      res_move = dfpn->best_move();
      break;
    }
    case hash("minimax"): {
      Minimax* minimax = new Minimax(game);
      minimax->getResult();
      res_move = minimax->best_move();
      break;
    }
    case hash("mini-ab"): {
      Minimax* minimax = new Minimax(game);
      minimax->getAlphaBetaResult();
      res_move = minimax->best_move();
      break;
    }
    case hash("mini-ab-tt"): {
      Minimax* minimax = new Minimax(game);
      minimax->getAlphaBetaTranspositionTableResult();
      res_move = minimax->best_move();
      break;
    }
    case hash("negamax"): {
      Negamax* negamax = new Negamax(game);
      negamax->getResult();
      res_move = negamax->best_move();
      break;
    }
    case hash("nega-ab"): {
      Negamax* negamax = new Negamax(game);
      negamax->getAlphaBetaResult();
      res_move = negamax->best_move();
      break;
    }
    case hash("nega-ab-tt"): {
      Negamax* negamax = new Negamax(game);
      negamax->getAlphaBetaTranspositionTableResult();
      res_move = negamax->best_move();
      break;
    }
    default: {
      res_move = Move{{0, 0}, 0};
      break;
    }
  }
  return res_move;
}

/**
 * @brief play a single match between agent p1 and agent p2.
 *        Board is square-shaped.
 * 
 * @param p1 
 * @param p2 
 * @param board_size 
 * @return true       if p1 wins
 * @return false      if p1 loss
 */
bool playSingleMatch(std::string p1, std::string p2, int board_size) {
  Game curr_game(generateBoardString(board_size));

  Move next_move = Move{{0, 0}, 0};

  uint16_t turn = 1;

  bool is_win = false;

  /////////////////////////////////////////////////
  cout << curr_game << endl;
  while (curr_game.isTerminal() == false) {
    if (turn % 2 == 1) {
      next_move = getMove(p1, curr_game);
      if (next_move.value == 0) {
        cout << "Turn " << turn << ": B (" << p1 << ") resigns." << endl;
        is_win = false;
        break;
      }
      cout << "Turn " << turn << ": B (" << p1 << ")  plays " << next_move.toString() << endl;
    } else {
      next_move = getMove(p2, curr_game);
      if (next_move.value == 0) {
        cout << "Turn " << turn << ": W (" << p2 << ") resigns." << endl;
        is_win = true;
        break;
      }
      cout << "Turn " << turn << ": W (" << p2 << ") plays " << next_move.toString() << endl;
    }
    curr_game.unsafePlay(next_move.pos, next_move.value);
    cout << curr_game << endl;
    turn += 1;
  }

  return is_win;
}

}  // namespace test

bool isValidAgentName(std::string name) {
  // TODO: how to make this easier...?
  if (name == "pns" || name == "dfpn" || name == "minimax" || name == "mini-ab" || name == "mini-ab-tt" || name == "negamax" || name == "nega-ab" || name == "nega-ab-tt") {
    return true;
  }
  return false;
}

void printHelp() {
  cout << "Usage ./other_tests <algo1-name> <algo2-name> <board-size>" << endl;
  cout << "--------------------------------------------------------------------" << endl;
  cout << "algo1 will go first." << endl;
  cout << "--------------------------------------------------------------------" << endl;
  cout << "Available Algorithms:" << endl;
  cout << "pns          Proof Number Search" << endl;
  cout << "dfpn         Depth-First Proof Number Search" << endl;
  cout << "minimax      Minimax" << endl;
  cout << "mini-ab      Minimax with Alpha-Beta Pruning" << endl;
  cout << "mini-ab-tt   Minimax with Alpha-Beta and Pruning Transposition Table" << endl;
  cout << "negamax      Negamax" << endl;
  cout << "nega-ab      Negamax with Alpha-Beta Pruning" << endl;
  cout << "nega-ab-tt   Negamax with Alpha-Beta Pruning and Transposition Table" << endl;
  cout << "--------------------------------------------------------------------" << endl;
  cout << "Availalbe Board Size: [2, 19]" << endl;
  cout << "Suggested Board Size: 3" << endl;
  cout << "--------------------------------------------------------------------" << endl;
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    printHelp();
    throw std::invalid_argument("Invalid inputs");
    return -1;
  }

  std::string player1(argv[1]);
  if (isValidAgentName(player1) == false) {
    printHelp();
    throw std::invalid_argument("Invalid algo1 name");
    return -1;
  }
  std::string player2(argv[2]);
  if (isValidAgentName(player2) == false) {
    printHelp();
    throw std::invalid_argument("Invalid algo1 name");
    return -1;
  }
  int board_size = atoi(argv[3]);
  if (board_size < 2 || board_size > 19) {
    printHelp();
    throw std::invalid_argument("Invalid board size");
    return -1;
  }

  test::playSingleMatch(player1, player2, board_size);

  return 0;
}