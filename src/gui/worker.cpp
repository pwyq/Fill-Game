/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 09:34:57
 * @modify date 2023-03-23 09:37:16
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

DFPNWorker::DFPNWorker() {
  // you could copy data from constructor arguments to internal variables here.
}

DFPNWorker::~DFPNWorker() {
  // free resources
}

void DFPNWorker::process(solver::Game* game) {
  solver::dfpn::DFPN* agent = new solver::dfpn::DFPN(*game);
  agent->solve();
  solver::helper::Move next_move = agent->best_move();
  emit finished(next_move);
  delete agent;
}

}  // namespace gui
