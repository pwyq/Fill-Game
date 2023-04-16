/**
 * @author      Junwen Shen, Yanqing Wu
 * @create date 2023-03-21 17:32:51
 * @modify date 2023-04-04 03:27:28
 * @desc Measure the average runtime and average peak RSS of algorithms
 */

// std
#include <fstream>
#include <iostream>
// local
#include "helper.h"
#include "solver/dfpn.h"
#include "solver/game.h"
#include "solver/helper.h"
#include "solver/mcts.h"
#include "solver/minimax.h"
#include "solver/negamax.h"
#include "solver/pns.h"

using solver::helper::getPeakRSS;
using solver::helper::Timer;
using solver::helper::toMilliseconds;

using fgtest::helper::hash;

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cout << "Usage: ./experiments <game_string> <algorithm>" << std::endl;
    return 1;
  }
  std::string game_string = argv[1];
  std::string algorithm   = argv[2];
  std::ofstream logFile;
  auto timer = Timer();
  switch (hash(algorithm)) {
    case hash("minimax"): {
      std::cout << "Run minimax on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game  = solver::Game(game_string);
      auto agent = solver::minimax::Minimax(game);
      timer.start();
      agent.getResult();
      timer.stop();
      auto peakRSS    = getPeakRSS();
      auto duration   = toMilliseconds(timer.duration()).count();
      auto node_count = agent.getNodeCount();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      std::cout << "Nodes opened: " << node_count << std::endl;
      logFile << node_count << std::endl;
      break;
    }
    case hash("minimax_alphabeta"): {
      std::cout << "Run minimax_alphabeta on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game  = solver::Game(game_string);
      auto agent = solver::minimax::Minimax(game);
      timer.start();
      agent.getAlphaBetaResult();
      timer.stop();
      auto peakRSS    = getPeakRSS();
      auto duration   = toMilliseconds(timer.duration()).count();
      auto node_count = agent.getNodeCount();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      std::cout << "Nodes opened: " << node_count << std::endl;
      logFile << node_count << std::endl;
      break;
    }
    case hash("minimax_alphabeta_tt"): {
      std::cout << "Run minimax_alphabeta_tt on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game  = solver::Game(game_string);
      auto agent = solver::minimax::Minimax(game);
      timer.start();
      agent.getAlphaBetaTranspositionTableResult();
      timer.stop();
      auto peakRSS    = getPeakRSS();
      auto duration   = toMilliseconds(timer.duration()).count();
      auto node_count = agent.getNodeCount();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      std::cout << "Nodes opened: " << node_count << std::endl;
      logFile << node_count << std::endl;
      break;
    }
    case hash("negamax"): {
      std::cout << "Run negamax on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game  = solver::Game(game_string);
      auto agent = solver::negamax::Negamax(game);
      timer.start();
      agent.getResult();
      timer.stop();
      auto peakRSS    = getPeakRSS();
      auto duration   = toMilliseconds(timer.duration()).count();
      auto node_count = agent.getNodeCount();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      std::cout << "Nodes opened: " << node_count << std::endl;
      logFile << node_count << std::endl;
      break;
    }
    case hash("negamax_alphabeta"): {
      std::cout << "Run negamax_alphabeta on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game  = solver::Game(game_string);
      auto agent = solver::negamax::Negamax(game);
      timer.start();
      agent.getAlphaBetaResult();
      timer.stop();
      auto peakRSS    = getPeakRSS();
      auto duration   = toMilliseconds(timer.duration()).count();
      auto node_count = agent.getNodeCount();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      std::cout << "Nodes opened: " << node_count << std::endl;
      logFile << node_count << std::endl;
      break;
    }
    case hash("negamax_alphabeta_tt"): {
      std::cout << "Run negamax_alphabeta_tt on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game  = solver::Game(game_string);
      auto agent = solver::negamax::Negamax(game);
      timer.start();
      agent.getAlphaBetaTranspositionTableResult();
      timer.stop();
      auto peakRSS    = getPeakRSS();
      auto duration   = toMilliseconds(timer.duration()).count();
      auto node_count = agent.getNodeCount();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      std::cout << "Nodes opened: " << node_count << std::endl;
      logFile << node_count << std::endl;
      break;
    }
    case hash("dfpn"): {
      std::cout << "Run dfpn on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game  = solver::Game(game_string);
      auto agent = solver::dfpn::DFPN(game);
      timer.start();
      agent.solve();
      timer.stop();
      auto peakRSS    = getPeakRSS();
      auto duration   = toMilliseconds(timer.duration()).count();
      auto node_count = agent.getNodeCount();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      std::cout << "Nodes opened: " << node_count << std::endl;
      logFile << node_count << std::endl;
      break;
    }
    case hash("pns"): {
      std::cout << "Run pns on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game  = solver::Game(game_string);
      auto agent = solver::pns::PNS(game);
      timer.start();
      agent.getResult();
      timer.stop();
      auto peakRSS    = getPeakRSS();
      auto duration   = toMilliseconds(timer.duration()).count();
      auto node_count = agent.getNodeCount();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      std::cout << "Nodes opened: " << node_count << std::endl;
      logFile << node_count << std::endl;
      break;
    }
    case hash("mcts"): {
      std::cout << "Run mcts on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game  = solver::Game(game_string);
      auto agent = solver::mcts::MCTS(game);
      timer.start();
      agent.search();
      timer.stop();
      auto peakRSS    = getPeakRSS();
      auto duration   = toMilliseconds(timer.duration()).count();
      auto node_count = agent.getNodeCount();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      std::cout << "Nodes opened: " << node_count << std::endl;
      logFile << node_count << std::endl;
      break;
    }
    default:
      std::cout << "No such algorithm: " << algorithm << std::endl;
      return 1;
  }
  logFile.close();
  return 0;
}
