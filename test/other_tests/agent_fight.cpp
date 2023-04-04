/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-04-03 21:34:32
 * @modify date 2023-04-03 21:34:32
 * @desc Test agents playing against each other
 * 
 * TODO: time constraint and memory constraint
 */

// std
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

namespace solver {

/**
 * @brief 
 * 
 * TODO: let it take input player1 and player2 (how?)
 * TODO: let it decide who play first
 * 
 */
void testAgentPlay() {
  // std::string board = "..*..";
  std::string board = "...*...*...";
  // std::string board = "....*....*....*....";
  Game curr_game(board);
  helper::Move next_move = helper::Move{{0, 0}, 0};

  uint turn = 1;

  pns::PNS* pns             = nullptr;
  negamax::Negamax* negamax = nullptr;

  //////////////////////
  cout << curr_game.toString() << endl;
  while (curr_game.isTerminal() == false) {
    if (turn % 2 == 0) {
      if (pns != nullptr) {
        delete pns;
        pns = nullptr;
      }
      pns = new pns::PNS(curr_game);

      pns->getResult();
      next_move = pns->best_move();

      if (next_move.value == 0) {
        cout << "Turn " << turn << ": B (PNS) resigns." << endl;
        break;
      }

      cout << "Turn " << turn << ": B (PNS)  plays " << next_move.toString() << endl;
    } else {
      if (negamax != nullptr) {
        delete negamax;
        negamax = nullptr;
      }
      negamax = new negamax::Negamax(curr_game);

      negamax->getAlphaBetaTranspositionTableResult();
      next_move = negamax->best_move();

      if (next_move.value == 0) {
        cout << "Turn " << turn << ": W (Nega) resigns." << endl;
        break;
      }

      cout << "Turn " << turn << ": W (Nega) plays " << next_move.toString() << endl;
    }

    curr_game.unsafePlay(next_move.pos, next_move.value);
    cout << curr_game.toString() << endl;
    turn += 1;
  }
}

}  // namespace solver

int main(int argc, char* argv[]) {
  solver::testAgentPlay();

  return 0;
}