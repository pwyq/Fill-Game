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
#include "solver/constraint.h"

// 1024 * 1024 * 1024 = 1073741824 Bytes = 1GB
constexpr size_t MEMORY_LIMIT = 1073741824;
constexpr size_t TIME_LIMIT   = 5;  // sec

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

      // TODO: the timer constraint works; Yanqing will have to investigate how to stop worker prematurely.
      //       SIGXCPU
      // ? None 4.5566 1173
      // QObject::~QObject: Timers cannot be stopped from another thread

      // solver::Constraint constraint = solver::Constraint(MEMORY_LIMIT, TIME_LIMIT);
      // solver::dfpn::DFPN::setConstraint(constraint);

      agent->solve();
      solver::helper::Move next_move = agent->bestMove();
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
