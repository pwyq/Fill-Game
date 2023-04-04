/**
 * @author      Yanqing Wu, Junwen Shen, Luke Kapeluck
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:34:19
 * @modify date 2023-03-21 15:23:13
 */
// std
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
// local
#include "solver/constraint.h"
#include "solver/dfpn.h"
#include "solver/game.h"
#include "solver/mcts.h"
#include "solver/minimax.h"
#include "solver/negamax.h"
#include "solver/pns.h"

using std::cout;
using std::endl;

namespace solver {

// 1024 * 1024 * 1024 = 1073741824 Bytes = 1GB
#define MEMORY_LIMIT (1073741824)

void startSolver(std::string& input, size_t time_limit) {
  if (!Game::isValidGameString(input)) {
    throw std::invalid_argument("Invalid game string");
  }
  Game game = Game(input);
  cout << game << endl;

  dfpn::DFPN dfpn(game);
  cout << "using DFPN..." << endl;
  // Constraint constraint = Constraint(MEMORY_LIMIT, time_limit);
  // constraint.signalHandler = DFPN::signalHandler;
  // constraint.apply();
  dfpn.solve();
  cout << dfpn.formatResult() << endl;

  minimax::Minimax minimax(game);
  cout << "using minimax..." << endl;
  cout << minimax.getResult() << endl;
  cout << minimax.bestMove().toString() << endl;
  cout << "using minimax-ab..." << endl;
  minimax = minimax::Minimax(game);
  cout << minimax.getAlphaBetaResult() << endl;
  cout << minimax.bestMove().toString() << endl;
  cout << "using minimax-ab-tt..." << endl;
  minimax = minimax::Minimax(game);
  cout << minimax.getAlphaBetaTranspositionTableResult() << endl;
  cout << minimax.bestMove().toString() << endl;

  negamax::Negamax negamax(game);
  cout << "using negamax..." << endl;
  cout << negamax.getResult() << endl;
  cout << negamax.bestMove().toString() << endl;
  cout << "using negamax-ab..." << endl;
  negamax = negamax::Negamax(game);
  cout << negamax.getAlphaBetaResult() << endl;
  cout << negamax.bestMove().toString() << endl;
  cout << "using negamax-ab-tt..." << endl;
  negamax = negamax::Negamax(game);
  cout << negamax.getAlphaBetaTranspositionTableResult() << endl;
  cout << negamax.bestMove().toString() << endl;

  pns::PNS pns(game);
  cout << "using pns..." << endl;
  cout << pns.getResult() << endl;
  cout << pns.bestMove().toString() << endl;

  mcts::MCTS mcts(game);
  cout << "using mcts..." << endl;
  mcts.search();
  cout << mcts.bestMove().toString() << endl;
}

/*
void testStackMemoryLimit() {  // SIGSEGV
  // long long arr[UINTMAX_MAX] = {0};    // this will give direct error;
  long long arr[10000] = {0};
  testStackMemoryLimit();
}

void testHeapMemoryLimit() {  // throw bad_alloc
  int* nmbr = new int[1024 * 1024 * 255];
}

void testTimeLimit() {  // SIGXCPU
  while (true) {
    cout << "time limit test\n";
  }
}
*/

}  // namespace solver

int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "invalid number of arguments = " << argc << endl;
    return -1;
  }
  std::string input_sequence = argv[1];
  int time_limit             = std::stoi(argv[2]);

  try {
    solver::startSolver(input_sequence, time_limit);
    // testStackMemoryLimit();
    // testHeapMemoryLimit();
    // testTimeLimit();
  } catch (const std::bad_alloc& e) {  // if a 'new' operator failed, it will throw a bad_alloc exception g_timer.stop();
    cout << "? None " << solver::dfpn::g_timer.duration().count() << " " << solver::dfpn::g_counter << endl;
  }
  return 0;
}

// End of File
