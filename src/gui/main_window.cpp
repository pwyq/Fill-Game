/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:32:27
 * @modify date 2023-02-11 16:12:10
 *
 * TODO: cell color (disabled cell)
 * TODO: save/load a game
 * TODO: timer on each side
 */
#include "gui/main_window.h"
// Qt
#include <QApplication>
// local
#include "gui/board_cell.h"
#include "gui/helper.h"
#include "gui/popup_selection.h"
#include "gui/popup_window.h"

using solver::helper::Move;

namespace gui {

MainWindow::MainWindow() : board_width_(2), board_height_(3), is_AI_(true) {
  // UI elements
  main_layout_       = new QHBoxLayout();
  board_layout_      = new QGridLayout();
  info_layout_       = new QGridLayout();
  main_widget_       = new QWidget();
  curr_player_label_ = new QLabel();
  browser_           = new QTextBrowser();

  // Solver elements
  this->startNewGame();

  // UI related
  game_menu_  = this->menuBar()->addMenu("&Game");
  board_menu_ = this->menuBar()->addMenu("&Board");
  help_menu_  = this->menuBar()->addMenu("&Help");
  this->initUI();
  // TODO: allow proportionally resize in the future
  this->setWindowFlags(windowFlags() & (~Qt::WindowMaximizeButtonHint));
  // https://en.cppreference.com/w/cpp/language/rule_of_three rule of 3/5/0
  // this->setAttribute( Qt::WA_DeleteOnClose );
}

void MainWindow::initUI() {
  this->setWindowTitle(QString::fromStdString("Fill Game"));
  this->initGameMenu();
  this->initBoardMenu();
  this->initHelpMenu();

  this->drawBoard();
  // init info layout
  info_layout_->addWidget(new QLabel("Current Player"), 0, 0, 1, 1);
  this->updateCurrentPlayer(this->game_->toPlay());
  info_layout_->addWidget(curr_player_label_, 0, 1, 1, 1);
  info_layout_->addWidget(browser_, 1, 0, 2, 2);

  main_layout_->addLayout(board_layout_);
  main_layout_->addLayout(info_layout_);
  main_widget_->setLayout(main_layout_);
  this->setCentralWidget(main_widget_);
}

void MainWindow::initGameMenu() {
  QAction *startNewGame = new QAction("Start &New Game", game_menu_);
  connect(startNewGame, &QAction::triggered,
          [this]() { this->startNewGame(); });
  game_menu_->addAction(startNewGame);

  game_menu_->addSeparator();

  QAction *quit = new QAction("&Quit", game_menu_);
  connect(quit, &QAction::triggered, [this]() { this->close(); });
  game_menu_->addAction(quit);
}

void MainWindow::initBoardMenu() {
  QAction *three = new QAction("3 x 3", board_menu_);
  connect(three, &QAction::triggered, [this]() { this->changeGameSize(3, 3); });
  board_menu_->addAction(three);

  QAction *five = new QAction("5 x 5", board_menu_);
  connect(five, &QAction::triggered, [this]() { this->changeGameSize(5, 5); });
  board_menu_->addAction(five);

  QAction *seven = new QAction("7 x 7", board_menu_);
  connect(seven, &QAction::triggered, [this]() { this->changeGameSize(7, 7); });
  board_menu_->addAction(seven);

  QAction *ten = new QAction("10 x 10", board_menu_);
  connect(ten, &QAction::triggered, [this]() { this->changeGameSize(10, 10); });
  board_menu_->addAction(ten);
  /*
  QAction* custom = new QAction("&Custom Board Size", _boardMenu);
  connect(ten, &QAction::triggered, [this]() {
      QStringList list = InputDialog::getStrings(this);
      if (!list.isEmpty()) {
          // use list
      }
      emit this->changeGameSize(10, 10);
  });
  _boardMenu->addAction(custom);
  */
}

void MainWindow::initHelpMenu() {
  QAction *rules = new QAction("&Rules", help_menu_);
  connect(rules, &QAction::triggered, []() {
    PopupWindow *a = new PopupWindow("Rules", "qrc:/resource/html/rules.html");
    a->setWindowSize(0.2, 0.4);
    a->move(QApplication::desktop()->screen()->rect().center() - a->frameGeometry().center());
    a->show();
  });
  help_menu_->addAction(rules);

  QAction *about = new QAction("&About", help_menu_);
  connect(about, &QAction::triggered, []() {
    PopupWindow *a = new PopupWindow("About", "qrc:/resource/html/about.html");
    a->setWindowSize(0.6, 0.8);
    a->move(QApplication::desktop()->screen()->rect().center() - a->frameGeometry().center());
    a->show();
  });
  help_menu_->addAction(about);
}

void MainWindow::startNewGame() {
  this->is_game_end_      = false;
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
  for (auto c : board_cells_) {
    c->setEnabled(true);
    c->setText("");
  }
  this->updateCurrentPlayer(this->game_->toPlay());
  browser_->clear();
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
  this->updateCurrentPlayer(this->game_->toPlay());
  browser_->clear();
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

// TODO: How to make a type T*& becomes T*??
// https://stackoverflow.com/questions/48023441/qt-type-as-parameter-of-function
// template<class T>
// void MainWindow::clearLayout(T* layout, bool deleteWidgets = true)
// void MainWindow::clearLayout(QGridLayout* layout, bool deleteWidgets = true)
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
    board_layout_->addWidget(new QLabel(uint8ToQstring(row)), row, 0, 1, 1);
  }
  // init board cells
  for (uint8_t row = 0; row < board_height_; row++) {
    for (uint8_t col = 0; col < board_width_; col++) {
      QString t         = "";
      BoardCell *button = new BoardCell(t, QPoint(col, row), this);  // note that col=x, row=y, from top down
      board_cells_.push_back(button);
      connect(button, &QPushButton::pressed, [button, this]() { this->onBoardCellPressed(button); });
      // offset each cell because of the x-y axis labels
      board_layout_->addWidget(button, row + 1, col + 1, 1, 1);
    }
  }
}

void MainWindow::playByAI() {
  // TODO: optimization, every time we are creating a new game and a new solver
  if (agent_dfpn_ != nullptr) {
    agent_dfpn_ = nullptr;
    delete agent_dfpn_;
  }
  agent_dfpn_ = new solver::dfpn::DFPN(*game_);
  agent_dfpn_->solve();
  Move nextMove = agent_dfpn_->best_move();
  if (nextMove.value == 0) {  // This may not be reached at all
    qDebug() << "no possible moves";
    return;
  }

  // Play
  this->game_->unsafePlay(nextMove.pos, nextMove.value);

  // GUI update
  BoardCell *cell = nullptr;
  for (auto c : this->board_cells_) {
    if (c->getPos().y() == nextMove.pos.row &&
        c->getPos().x() == nextMove.pos.col) {
      cell = c;
    }
  }
  QString moveValue = uint8ToQstring(nextMove.value);
  cell->setText(moveValue);
  cell->setEnabled(false);
  this->browser_->append(this->getMoveMessage(nextMove.pos, moveValue));
  this->updateCurrentPlayer(this->game_->toPlay());

  // Game update
  this->game_string_ = this->game_->toString();
  delete this->game_;
  this->game_ = new solver::Game(this->game_string_);
  if (game_->getPossibleMoves().size() == 0) {
    this->is_game_end_ = true;
    QString s          = "AI wins!";
    this->displayMessage(s);
  }
}

void MainWindow::onBoardCellPressed(BoardCell *cell) {
  if (this->is_game_end_) {
    QString s = "Game is ended. Please start a new game.";
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
  connect(pop_selection_, &PopupSelection::selectedNumber,
          [cell, cellPos, this](QString moveValue) {
            cell->setText(moveValue);
            this->game_->unsafePlay(cellPos, QStringToUint8(moveValue));
            this->game_string_ = this->game_->toString();
            delete this->game_;
            this->game_ = new solver::Game(this->game_string_);

            this->browser_->append(this->getMoveMessage(cellPos, moveValue));
            if (this->game_->getPossibleMoves().size() == 0) {
              // user clicked a dead cell
              pop_selection_->close();
              this->is_game_end_ = true;
              QString s          = "Winner: " + this->curr_player_label_->text();
              this->displayMessage(s);
            } else {
              // the move was successful
              cell->setEnabled(false);
              this->updateCurrentPlayer(this->game_->toPlay());
              pop_selection_->close();
            }
            this->is_select_done_ = true;
            if (true == this->is_AI_) {
              this->playByAI();
            }
          });
  pop_selection_->move(QCursor::pos());
  pop_selection_->show();
}

}  // namespace gui