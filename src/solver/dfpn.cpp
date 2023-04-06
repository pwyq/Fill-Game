/**
 * @author      Yanqing Wu, Junwen Shen, Luke Kapeluck
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:33:41
 * @modify date 2023-02-10 05:33:41
 */
#include "solver/dfpn.h"
// std
#include <csignal>
#include <iostream>
// local
#include "solver/game.h"
#include "solver/node.h"

using solver::helper::LOSS;
using solver::helper::WIN;

namespace solver::dfpn {

helper::Timer<> g_timer{};  // total time used
size_t g_counter = 0;       // num node visited

DFPN::DFPN(const Game &game) : root_(game) { }

#if defined(__linux__)
void DFPN::signalHandler(int sig) {
  switch (sig) {
      case SIGSEGV:
          std::cerr << "SIGSEGV" << std::endl;
          break;
      case SIGXCPU:
          std::cerr << "SIGXCPU" << std::endl;
          break;
      case SIGALRM:
          std::cerr << "SIGALRM" << std::endl;
          break;
      default:
          break;
  }
  g_timer.stop();
  std::cout << "? None " << g_timer.duration().count() << " " << g_counter
            << std::endl;
  exit(EXIT_FAILURE);
}
#endif

[[maybe_unused]] void DFPN::setConstraint(Constraint &constraint) {
#if defined(__linux__)
  constraint.signalHandler = signalHandler;
  constraint.apply();
#endif
}

void DFPN::solve() {
  if (!constrained) {
    g_timer.start();
    if (root_.game_.isTerminal()) {
        result_ = LOSS;
        g_timer.stop();
        return;
    }
    MID(root_);
    result_ = (root_.delta_ == INF) ? WIN : LOSS;
    g_timer.stop();
  } else {
    auto func = [this](std::atomic<helper::Move>& move, const std::stop_token &stop_token) {
      this->token = stop_token;
      g_timer.start();
      if (root_.game_.isTerminal()) {
        result_ = LOSS;
        g_timer.stop();
        return;
      }
      MID(root_);
      result_ = (root_.delta_ == INF) ? WIN : LOSS;
      g_timer.stop();
    };
    (void)helper::timeout(time_limit_, func, best_move_);
  }
}

void DFPN::MID(Node &node) {  // NOLINT
  ++g_counter;
  if (token.stop_requested() || node.game_.isTerminal()) {
    saveProofAndDisproofNumbers(node, node.phi_, node.delta_);
    return;
  }
  node.generateChildren();

  uint32_t phi   = computeSumPhi(node);
  uint32_t delta = computeMinDelta(node);
  uint32_t child_phi, delta_2;
  // the node must have at least one child at this point; otherwise it's a
  // terminal
  uint32_t best_child_index = 0;
  // uint32_t best_child_index = UINT16_MAX;

  while (node.phi_ > delta && node.delta_ > phi) {
    best_child_index = selectChild(node, child_phi, delta_2);
    auto &best_child = node.children_[best_child_index];
    best_child.phi_  = node.delta_ + child_phi - phi;
    if (best_child.phi_ > INF) {
      best_child.phi_ = INF;
    }
    if (delta_2 != INF) {
      ++delta_2;
    }
    best_child.delta_ = (std::min)(node.phi_, delta_2);
    MID(best_child);
    phi   = computeSumPhi(node);
    delta = computeMinDelta(node);
  }
  // store search results
  node.phi_   = delta;
  node.delta_ = phi;
  best_move_.store(node.children_[best_child_index].move_);
  /*
  if (best_child_index != UINT16_MAX) {
      best_move = node.children[best_child_index].move;
  } else {
      best_move = node.children[0].move;  // if not being updated, then it has
  only one child
  }
  */
  saveProofAndDisproofNumbers(node, node.phi_, node.delta_);
}

size_t DFPN::selectChild(Node &node, uint32_t &child_phi, uint32_t &delta_2) {
  size_t best_child_index = 0;
  child_phi               = INF;
  uint32_t child_delta    = INF;
  uint32_t phi, delta;
  for (size_t i = 0; i < node.children_.size(); ++i) {
    auto &child = node.children_[i];
    retrieveProofAndDisproofNumbers(child, phi, delta);
    if (delta < child_delta) {
      best_child_index = i;
      delta_2          = child_delta;
      child_phi        = phi;
      child_delta      = delta;
    } else if (delta < delta_2) {
      delta_2 = delta;
    }
    /**
    if (phi == INF) {
        return best_child_index;
    }
    **/
    //        ++g_counter;
  }
  return best_child_index;
}

void DFPN::retrieveProofAndDisproofNumbers(Node &node, uint32_t &phi,
                                           uint32_t &delta) {
  if (tt_.find(node.id_) != tt_.end()) {
    auto &v = tt_[node.id_];
    phi     = v.first;
    delta   = v.second;
  } else {
    phi   = node.phi_;
    delta = node.delta_;
  }
}

uint32_t DFPN::computeMinDelta(Node &node) {
  uint32_t _min = INF;
  uint32_t _phi, _delta;
  for (auto &child : node.children_) {
    retrieveProofAndDisproofNumbers(child, _phi, _delta);
    _min = (std::min)(_min, _delta);
  }
  return _min;
}

uint32_t DFPN::computeSumPhi(Node &node) {
  uint32_t _sum = 0;
  uint32_t _phi, _delta;
  for (auto &child : node.children_) {
    retrieveProofAndDisproofNumbers(child, _phi, _delta);
    if (_phi == INF) {
      _sum = INF;
      break;
    }
    _sum += _phi;
  }
  return _sum;
}

std::string DFPN::formatResult() const {
  std::string ret;
  switch (result_) {
    case WIN:
      ret += "W ";
      ret += best_move_.load().toString() + " ";
      ret += std::to_string(g_timer.duration().count()) + " ";
      ret += std::to_string(g_counter);
      break;
    case LOSS:
      ret += "L None ";
      ret += std::to_string(g_timer.duration().count()) + " ";
      ret += std::to_string(g_counter);
      break;
    default:  // Handled by signal handler
      break;
  }
  return ret;
}

short DFPN::getResult() const {
  switch (result_) {
    case WIN:
      return 1;
    case LOSS:
      return -1;
    default:  // Handled by signal handler
      return 0;
  }
}

void DFPN::setTimeConstraint(size_t time_limit) {
  constrained = true;
  time_limit_ = std::chrono::seconds(time_limit);
}

}  // namespace solver::dfpn
