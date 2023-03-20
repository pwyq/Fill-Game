/**
 * @author      Yanqing Wu, Junwen Shen, Luke Kapeluck
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:34:19
 * @modify date 2023-03-18 22:23:51
 */
// std
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
// local
//#include "solver/constraint.h"
#include "solver/dfpn.h"
#include "solver/game.h"
#include "solver/minimax.h"
#include "solver/negamax.h"
#include "solver/pns.h"

using std::cout;
using std::endl;

namespace solver {

// 1024 * 1024 * 1024 = 1073741824 Bytes = 1GB
#define MEMORY_LIMIT (1073741824)

void startSolver(std::string& input, size_t time_limit) {
  Game game(input);
  cout << game << endl;

  cout << "using DFPN..." << endl;
  dfpn::DFPN dfpn(game);
  // Constraint constraint    = Constraint(MEMORY_LIMIT, time_limit);
  // constraint.signalHandler = DFPN::signalHandler;
  // constraint.apply();
  dfpn.solve();
  cout << dfpn.formatResult() << endl;

  cout << "using minimax..." << endl;
  minimax::Minimax minimax(game);
  // cout << minimax.getResult() << endl;
  cout << minimax.getAlphaBetaResult() << endl;
  cout << minimax.getAlphaBetaTranspositionTableResult() << endl;

  cout << "using negamax..." << endl;
  negamax::Negamax negamax(game);
  // cout << negamax.getResult() << endl;
  cout << negamax.getAlphaBetaResult() << endl;
  cout << negamax.getAlphaBetaTranspositionTableResult() << endl;

  cout << "using pns..." << endl;
  pns::PNS pns(game);
  cout << pns.getResult() << endl;
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
  // if (argc != 3) {
  //   cout << "invalid number of arguments = " << argc << endl;
  //   return -1;
  // }
  // std::string input_sequence = argv[1];
  // int time_limit             = std::stoi(argv[2]);
  std::string input_sequence = "1..*.2.";
  int time_limit             = 1;

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
