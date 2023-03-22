/**
 * @author    Junwen Shen
 * @create date 2023-03-21 17:32:51
 * @modify date 2023-03-21 17:32:51
 *
 */
// std
#include <fstream>
#include <iostream>
// local
#include "dfpn.h"
#include "game.h"
#include "helper.h"
#include "minimax.h"
#include "negamax.h"
#include "pns.h"

/**
 * source: https://stackoverflow.com/a/46711735
 * @param data
 * @param size
 * @return
 */
static constexpr uint32_t hash(const std::string_view& string) noexcept{
  uint32_t hash = 5381;
  for (const auto &c : string) {
    hash = ((hash << 5) + hash) + (unsigned char)c;
  }
  return hash;
}

static constexpr auto toMilliseconds(const auto& duration) {
  return std::chrono::duration<double, std::milli>(duration);
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "Usage: ./experiments <game_string> <algorithm>" << std::endl;
    return 1;
  }
  std::string game_string = argv[1];
  std::string algorithm = argv[2];
  std::ofstream logFile;
  auto timer = solver::helper::Timer();
  switch (hash(algorithm)) {
    case hash("minimax"): {
      std::cout << "Run minimax on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game = solver::Game(game_string);
      auto agent = solver::minimax::Minimax(game);
      timer.start();
      agent.getResult();
      timer.stop();
      auto peakRSS = solver::helper::getPeakRSS();
      auto duration = toMilliseconds(timer.duration()).count();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      break;
    }
    case hash("minimax_alphabeta"): {
      std::cout << "Run minimax_alphabeta on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game = solver::Game(game_string);
      auto agent = solver::minimax::Minimax(game);
      timer.start();
      agent.getAlphaBetaResult();
      timer.stop();
      auto peakRSS = solver::helper::getPeakRSS();
      auto duration = toMilliseconds(timer.duration()).count();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      break;
    }
    case hash("minimax_alphabeta_tt"): {
      std::cout << "Run minimax_alphabeta_tt on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game = solver::Game(game_string);
      auto agent = solver::minimax::Minimax(game);
      timer.start();
      agent.getAlphaBetaTranspositionTableResult();
      timer.stop();
      auto peakRSS = solver::helper::getPeakRSS();
      auto duration = toMilliseconds(timer.duration()).count();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      break;
    }
    case hash("negamax"): {
      std::cout << "Run negamax on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game = solver::Game(game_string);
      auto agent = solver::negamax::Negamax(game);
      timer.start();
      agent.getAlphaBetaTranspositionTableResult();
      timer.stop();
      auto peakRSS = solver::helper::getPeakRSS();
      auto duration = toMilliseconds(timer.duration()).count();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      break;
    }
    case hash("negamax_alphabeta"): {
      std::cout << "Run negamax_alphabeta on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game = solver::Game(game_string);
      auto agent = solver::negamax::Negamax(game);
      timer.start();
      agent.getAlphaBetaTranspositionTableResult();
      timer.stop();
      auto peakRSS = solver::helper::getPeakRSS();
      auto duration = toMilliseconds(timer.duration()).count();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      break;
    }
    case hash("negamax_alphabeta_tt"): {
      std::cout << "Run negamax_alphabeta_tt on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game = solver::Game(game_string);
      auto agent = solver::negamax::Negamax(game);
      timer.start();
      agent.getAlphaBetaTranspositionTableResult();
      timer.stop();
      auto peakRSS = solver::helper::getPeakRSS();
      auto duration = toMilliseconds(timer.duration()).count();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      break;
    }
    case hash("dfpn"): {
      std::cout << "Run dfpn on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game = solver::Game(game_string);
      auto agent = solver::dfpn::DFPN(game);
      timer.start();
      agent.solve();
      timer.stop();
      auto peakRSS = solver::helper::getPeakRSS();
      auto duration = toMilliseconds(timer.duration()).count();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      break;
    }
    case hash("pns"): {
      std::cout << "Run pns on " << game_string << std::endl;
      logFile.open(algorithm + ".log", std::ios::app);
      logFile << game_string << std::endl;
      auto game = solver::Game(game_string);
      auto agent = solver::pns::PNS(game);
      timer.start();
      agent.getResult();
      timer.stop();
      auto peakRSS = solver::helper::getPeakRSS();
      auto duration = toMilliseconds(timer.duration()).count();
      std::cout << "Peak RSS: " << peakRSS << std::endl;
      logFile << peakRSS << std::endl;
      std::cout << "Duration: " << duration << std::endl;
      logFile << duration << std::endl;
      break;
    }
    default:
      std::cout << "No such algorithm: " << algorithm << std::endl;
      return 1;
  }
  logFile.close();
  return 0;
}
