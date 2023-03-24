/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:32:27
 * @modify date 2023-03-24 01:24:22
 *
 * TODO: same timer constraint (as the UI) on solver
 * TODO: save/load a game ?
 */
#include "gui/main_window.h"
// Qt
#include <QThread>
// local
#include "gui/board_cell.h"
#include "gui/helper.h"
#include "gui/popup_selection.h"

using solver::helper::Move;

namespace gui {

MainWindow::MainWindow() : board_width_(2), board_height_(3), is_AI_(true) {
  // This meta-type must be placed inside the constructor
  qRegisterMetaType<solver::helper::Move>();

  // UI elements
  main_layout_  = new QHBoxLayout();
  board_layout_ = new QGridLayout();
  main_widget_  = new QWidget();
  info_dock_    = InfoDock::GetInstance();
  menu_bar_     = MainWindowMenuBar::GetInstance(this);

  // Solver elements
  this->startNewGame();

  // UI related
  this->initUI();
  // TODO: allow proportionally resize in the future
  this->setWindowFlags(windowFlags() & (~Qt::WindowMaximizeButtonHint));
  // https://en.cppreference.com/w/cpp/language/rule_of_three rule of 3/5/0
  // this->setAttribute( Qt::WA_DeleteOnClose );

  // testing
  tcp_server_ = new TCPServer(this);
  tcp_client_ = new TCPClient(this);

  tcp_server_->sendMessage();
}

void MainWindow::initUI() {
  // Top Menu Bar
  this->setWindowTitle(QString::fromStdString("Fill Game"));
  connect(menu_bar_, &MainWindowMenuBar::startNewGame, this, &MainWindow::startNewGame);
  connect(menu_bar_, &MainWindowMenuBar::changeGameSize, this, &MainWindow::changeGameSize);
  connect(menu_bar_, &MainWindowMenuBar::selectOpponent, this, &MainWindow::onSelectOpponent);
  this->setMenuBar(menu_bar_);

  // Central Area
  this->drawBoard();
  // Right Info Dock
  connect(info_dock_, &InfoDock::gameTimeOut, [this](QString msg) {
    this->is_game_end_ = true;
    this->displayMessage(msg);
  });
  connect(this, &MainWindow::stopGameTimer, info_dock_, &InfoDock::onStopGameTimer);
  this->addDockWidget(Qt::RightDockWidgetArea, info_dock_);

  main_layout_->addLayout(board_layout_);
  main_widget_->setLayout(main_layout_);
  this->setCentralWidget(main_widget_);
}

void MainWindow::startNewGame() {
  is_game_end_ = false;
  is_AI_turn_  = false;

  std::string _gameString = "";
  for (uint8_t row = 0; row < board_height_; row++) {
    for (uint8_t col = 0; col < board_width_; col++) {
      _gameString += ".";
    }
    _gameString += "*";
  }
  _gameString.pop_back();

  if (game_ != nullptr) {
    game_ = nullptr;
    delete game_;
  }
  game_ = new solver::Game(_gameString);

  // clear UI
  move_counter_ = 1;

  for (auto c : board_cells_) {
    c->setEnabled(true);
    c->setText("");
  }
  info_dock_->resetPlayer();
  info_dock_->browser()->clear();
}

void MainWindow::changeGameSize(uint8_t width, uint8_t height) {
  is_game_end_            = false;
  board_height_           = height;
  board_width_            = width;
  std::string _gameString = "";
  for (uint8_t row = 0; row < board_height_; row++) {
    for (uint8_t col = 0; col < board_width_; col++) {
      _gameString += ".";
    }
    _gameString += "*";
  }
  _gameString.pop_back();

  if (game_ != nullptr) {
    game_ = nullptr;
    delete game_;
  }
  game_ = new solver::Game(_gameString);

  // redraw & clear UI
  this->clearBoardLayout();
  board_cells_.clear();
  this->drawBoard();
  info_dock_->resetPlayer();
  info_dock_->browser()->clear();
  // TODO: resize window to board
  // qDebug() << this->_mainWidget->size();
  // qDebug() << this->_mainWidget->sizeHint();
  // qDebug() << this->_mainWidget->minimumSizeHint();
  // this->resize(this->_mainWidget->minimumSizeHint());
  for (uint8_t i = 0; i < 2; i++)
    this->adjustSize();  // TODO: not fully working; if the board change form
                         // large to small for the first time, it will not work;
                         // all other cases work fine. Current work around is to
                         // start with the smallest board
}

void MainWindow::clearBoardLayout() {
  while (board_layout_->count() > 0) {
    auto item = board_layout_->itemAt(0)->widget();
    item->deleteLater();
    delete item;
  }
}

void MainWindow::drawBoard() {
  // init board x y axis
  for (uint8_t col = 1; col < board_width_ + 1; col++) {
    char c    = 64 + col;  // ascii 'A' = 65
    QLabel *l = new QLabel(QChar(c));
    l->setAlignment(Qt::AlignCenter);
    board_layout_->addWidget(l, 0, col, 1, 1);
  }
  for (uint8_t row = 1; row < board_height_ + 1; row++) {
    board_layout_->addWidget(new QLabel(helper::uint8ToQstring(row)), row, 0, 1, 1);
  }
  // init board cells
  for (uint8_t row = 0; row < board_height_; row++) {
    for (uint8_t col = 0; col < board_width_; col++) {
      QString t         = "";
      BoardCell *button = new BoardCell(t, QPoint(col, row), this);  // note that col=x, row=y, from top down
      board_cells_.push_back(button);
      connect(button, &QPushButton::pressed, [button, this]() {
        this->onBoardCellPressed(button);
      });
      // offset each cell because of the x-y axis labels
      board_layout_->addWidget(button, row + 1, col + 1, 1, 1);
    }
  }
}

void MainWindow::playByAI() {
  is_AI_turn_ = true;
  solverController();
}

void MainWindow::solverController() {
  QThread *thread      = new QThread;
  SolverWorker *worker = new SolverWorker(solver_);
  worker->moveToThread(thread);
  // connects the thread’s started() signal to the processing() slot in the worker, causing it to start.
  connect(thread, &QThread::started, worker, [worker, this]() {
    worker->process(this->game_);
  });
  connect(worker, &SolverWorker::finished, this, &MainWindow::onSolverFinished);
  // when the worker instance emits finished(), it will signal the thread to quit, i.e. shut down.
  connect(worker, &SolverWorker::finished, thread, &QThread::quit);
  // mark the worker instance using the same finished() signal for deletion.
  connect(worker, &SolverWorker::finished, worker, &QObject::deleteLater);
  // to prevent crashes because the thread hasn’t fully shut down yet when it is deleted,
  //  we connect the finished() of the thread (not the worker!) to its own deleteLater() slot.
  //  This will cause the thread to be deleted only after it has fully shut down.
  connect(thread, &QThread::finished, thread, &QThread::deleteLater);
  thread->start();
}

void MainWindow::onBoardCellPressed(BoardCell *cell) {
  tcp_server_->sendMessage();

  if (is_game_end_) {
    QString s = "Game is ended. Please start a new game.";
    this->displayMessage(s);
    return;
  }
  if (is_AI_turn_) {
    QString s = "AI is thinking... Please wait...";
    this->displayMessage(s);
    return;
  }
  // _mainWidget->setEnabled(false);    // prevent from clicking another cell
  Pos cellPos = Pos{static_cast<uint8_t>(cell->getPos().y()),
                    static_cast<uint8_t>(cell->getPos().x())};

  auto allMoves = game_->getPossibleMoves();
  if (allMoves.find(cellPos) == allMoves.end()) {
    this->displayMessage("No Possible Move");
    cell->setEnabled(false);
    return;
  }
  auto moves = allMoves.at(cellPos);

  if (true == is_select_done_) {
    is_select_done_ = false;
  } else {
    pop_selection_->deleteLater();
    delete pop_selection_;
  }
  pop_selection_ = PopupSelection::GetInstance(moves);
  connect(pop_selection_, &PopupSelection::selectedNumber, [cell, cellPos, this](QString moveValue) {
    cell->setText(moveValue, game_->toPlay());
    game_->unsafePlay(cellPos, helper::QStringToUint8(moveValue));
    game_string_ = game_->toString();
    delete game_;
    game_ = new solver::Game(game_string_);
    info_dock_->browser()->append(this->getMoveMessage(cellPos, moveValue));
    if (game_->getPossibleMoves().size() == 0) {
      // user clicked a dead cell
      pop_selection_->close();
      is_game_end_ = true;
      emit this->stopGameTimer();
      QString s = "Winner: " + info_dock_->getCurrentPlayer();
      this->displayMessage(s);
    } else {
      // the move was successful
      cell->setEnabled(false);
      info_dock_->updatePlayer();
      pop_selection_->close();
    }
    is_select_done_ = true;
    if (true == is_AI_) {
      this->playByAI();
    }
  });
  pop_selection_->move(QCursor::pos());
  pop_selection_->show();
}

void MainWindow::onSolverFinished(solver::helper::Move next_move) {
  if (is_game_end_) {
    qDebug() << "Game is already ended. AI lost...";
    return;
  }

  if (next_move.value == 0) {  // This may not be reached at all
    qDebug() << "no possible moves";
    return;
  }

  // Play
  game_->unsafePlay(next_move.pos, next_move.value);

  // GUI update
  BoardCell *cell = nullptr;
  for (auto c : board_cells_) {
    if (c->getPos().y() == next_move.pos.row &&
        c->getPos().x() == next_move.pos.col) {
      cell = c;
    }
  }
  QString moveValue = helper::uint8ToQstring(next_move.value);
  cell->setText(moveValue);
  cell->setEnabled(false);
  info_dock_->browser()->append(this->getMoveMessage(next_move.pos, moveValue));
  info_dock_->updatePlayer();

  // Game update
  game_string_ = game_->toString();
  delete game_;
  game_ = new solver::Game(game_string_);
  if (game_->getPossibleMoves().size() == 0) {
    is_game_end_ = true;
    emit this->stopGameTimer();
    QString s = "AI wins!";
    this->displayMessage(s);
  }

  is_AI_turn_ = false;
  return;
}

void MainWindow::onSelectOpponent(helper::SOLVER opponent) {
  if (solver_ == opponent) {
    QString s = "[WARNING] same opponent. no change is made";
    info_dock_->browser()->append(s);
    return;
  }
  solver_ = opponent;

  QString out_str;
  switch (solver_) {
    case helper::SOLVER::DFPN: {
      is_AI_  = true;
      out_str = "[INFO] switch to opponent=DFPN";
      break;
    }
    case helper::SOLVER::PNS: {
      // TODO
      is_AI_  = true;
      out_str = "[INFO] switch to opponent=PNS";
      break;
    }
    case helper::SOLVER::MINIMAX_AB_TT: {
      // TODO
      is_AI_  = true;
      out_str = "[INFO] switch to opponent=MINIMAX_AB_TT";
      break;
    }
    case helper::SOLVER::NEGAMAX_AB_TT: {
      // TODO
      is_AI_  = true;
      out_str = "[INFO] switch to opponent=NEGAMAX_AB_TT";
      break;
    }
    case helper::SOLVER::HUMAN_REMOTE: {
      is_AI_  = false;
      out_str = "[INFO] switch to opponent=Human (remote)";
      break;
    }
    case helper::SOLVER::HUMAN_LOCAL: {
      is_AI_  = false;
      out_str = "[INFO] switch to opponent=Human (local)";
      break;
    }
  }
  info_dock_->browser()->append(out_str);

  return;
}

}  // namespace gui