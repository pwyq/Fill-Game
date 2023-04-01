/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 09:34:57
 * @modify date 2023-03-26 02:51:48
 */

#include "gui/worker.h"
// Qt
#include <QDebug>

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
  // TODO: other than the switch cases,
  //    how to better generalize worker to different solvers, given that it's impossible to use template for Qt's slots/signals?

  switch (solver_) {
    case helper::SOLVER::DFPN: {
      solver::dfpn::DFPN* agent = new solver::dfpn::DFPN(*game);
      agent->solve();
      solver::helper::Move next_move = agent->best_move();
      emit finished(next_move);
      delete agent;
      break;
    }
    case helper::SOLVER::PNS: {
      // TODO
      break;
    }
    case helper::SOLVER::MINIMAX_AB_TT: {
      // TODO
      break;
    }
    case helper::SOLVER::NEGAMAX_AB_TT: {
      // TODO
      break;
    }
    default: {
      break;
    }
  }
}

}  // namespace gui
