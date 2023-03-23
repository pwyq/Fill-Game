/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 09:32:13
 * @modify date 2023-03-23 15:35:47
 * @desc Worker Thread. To use for jobs outside of the main thread (i.e. GUI thread)
 * 
 * https://mayaposch.wordpress.com/2011/11/01/how-to-really-truly-use-qthreads-the-full-explanation/
 * 
 * 0. one extremely important thing to note:
 *      you should NEVER allocate heap objects (using new) in the constructor of the QObject class 
 *      as this allocation is then performed on the main thread and not on the new QThread instance, 
 *      meaning that the newly created object is then owned by the main thread and not the QThread instance.
 * 1. https://stackoverflow.com/questions/26950718/how-to-use-templates-with-qt-signals-and-slots
 *      It it IMPOSSIBLE to use template in Qt slots & signals.
 * 2. Passing values by reference in signal/slot connections is not a good idea.
 */

#ifndef FG_GUI_WORKER_H_
#define FG_GUI_WORKER_H_
// qt
#include <QObject>
// local
#include "gui/helper.h"
#include "solver/dfpn.h"
#include "solver/game.h"
#include "solver/helper.h"

namespace gui {

class Worker : public QObject {
  Q_OBJECT
 public:
  Worker();
  ~Worker();
 public slots:
  void process();
 signals:
  void finished();
  void error(QString err);
};

// TODO: how to use inheritence here?
class SolverWorker : public QObject {
  Q_OBJECT
 public:
  SolverWorker(helper::SOLVER solver);
  ~SolverWorker();
 public slots:
  void process(solver::Game* game);

 private:
  helper::SOLVER solver_;
 signals:
  void finished(solver::helper::Move move);
  // void error(QString err);
};

}  // namespace gui

#endif
