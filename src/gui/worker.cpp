/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 09:34:57
 * @modify date 2023-03-26 02:51:48
 */

#include "gui/worker.h"
// Qt
#include <QDebug>
// local
#include "solver/dfpn.h"
#include "solver/minimax.h"
#include "solver/negamax.h"
#include "solver/pns.h"

namespace gui {

Worker::Worker() {
  // you could copy data from constructor arguments to internal variables here.
}

Worker::~Worker() {
  // free resources
}

void Worker::process() {
  // allocate resources using new here
  qDebug() << "Hello World!";
  emit finished();
}

///////////////////////////////////////
// SolverWorker
///////////////////////////////////////

SolverWorker::SolverWorker(helper::SOLVER solver) : solver_(solver) {
  // you could copy data from constructor arguments to internal variables here.
}

SolverWorker::~SolverWorker() {
  // free resources
}

void SolverWorker::process(solver::Game* game) {
  switch (solver_) {
    case helper::SOLVER::DFPN: {
      solver::dfpn::DFPN* agent = new solver::dfpn::DFPN(*game);
      agent->solve();
      solver::helper::Move next_move = agent->bestMove();
      emit finished(next_move);
      delete agent;
      break;
    }
    case helper::SOLVER::PNS: {
      solver::pns::PNS* agent = new solver::pns::PNS(*game);
      agent->getResult();
      solver::helper::Move next_move = agent->bestMove();
      emit finished(next_move);
      delete agent;
      break;
    }
    case helper::SOLVER::MINIMAX_AB_TT: {
      solver::minimax::Minimax* agent = new solver::minimax::Minimax(*game);
      agent->getAlphaBetaTranspositionTableResult();
      solver::helper::Move next_move = agent->bestMove();
      emit finished(next_move);
      delete agent;
      break;
    }
    case helper::SOLVER::NEGAMAX_AB_TT: {
      solver::negamax::Negamax* agent = new solver::negamax::Negamax(*game);
      agent->getAlphaBetaTranspositionTableResult();
      solver::helper::Move next_move = agent->bestMove();
      emit finished(next_move);
      delete agent;
      break;
    }
    default: {
      break;
    }
  }
}

}  // namespace gui
