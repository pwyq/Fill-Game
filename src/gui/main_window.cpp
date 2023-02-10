/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:32:27
 * @modify date 2023-02-10 05:32:27
 *
 * TODO: cell color (disabled cell)
 * TODO: save/load a game
 * TODO: timer on each side
 */
// Qt
#include <QMessageBox>
// local
#include "gui/board_cell.h"
#include "gui/helper.h"
#include "gui/main_window.h"
#include "gui/popup_selection.h"

namespace GUI {

MainWindow::MainWindow() : _boardWidth(2), _boardHeight(3), _isAI(true) {
  // UI elements
  _mainLayout = new QHBoxLayout();
  _boardLayout = new QGridLayout();
  _infoLayout = new QGridLayout();
  _mainWidget = new QWidget();
  _currPlayer = new QLabel();
  _browser = new QTextBrowser();

  // Solver elements
  this->startNewGame();

  // UI related
  _gameMenu = this->menuBar()->addMenu("&Game");
  _boardMenu = this->menuBar()->addMenu("&Board");
  this->initUI();
  this->setWindowFlags(
      windowFlags() &
      (~Qt::WindowMaximizeButtonHint));  // TODO: allow proportionally resize in
                                         // the future
  // https://en.cppreference.com/w/cpp/language/rule_of_three rule of 3/5/0
  // this->setAttribute( Qt::WA_DeleteOnClose );
}

void MainWindow::initUI() {
  this->setWindowTitle(QString::fromStdString("Fill Game"));
  this->initGameMenu();
  this->initBoardMenu();

  this->drawBoard();
  // init info layout
  _infoLayout->addWidget(new QLabel("Current Player"), 0, 0, 1, 1);
  this->updateCurrentPlayer(this->_game->to_play);
  _infoLayout->addWidget(_currPlayer, 0, 1, 1, 1);
  _infoLayout->addWidget(_browser, 1, 0, 2, 2);

  _mainLayout->addLayout(_boardLayout);
  _mainLayout->addLayout(_infoLayout);
  _mainWidget->setLayout(_mainLayout);
  this->setCentralWidget(_mainWidget);
}

void MainWindow::initGameMenu() {
  QAction *startNewGame = new QAction("Start &New Game", _gameMenu);
  connect(startNewGame, &QAction::triggered,
          [this]() { this->startNewGame(); });
  _gameMenu->addAction(startNewGame);

  _gameMenu->addSeparator();

  QAction *quit = new QAction("&Quit", _gameMenu);
  connect(quit, &QAction::triggered, [this]() { this->close(); });
  _gameMenu->addAction(quit);
}

void MainWindow::initBoardMenu() {
  QAction *three = new QAction("3 x 3", _boardMenu);
  connect(three, &QAction::triggered, [this]() { this->changeGameSize(3, 3); });
  _boardMenu->addAction(three);

  QAction *five = new QAction("5 x 5", _boardMenu);
  connect(five, &QAction::triggered, [this]() { this->changeGameSize(5, 5); });
  _boardMenu->addAction(five);

  QAction *seven = new QAction("7 x 7", _boardMenu);
  connect(seven, &QAction::triggered, [this]() { this->changeGameSize(7, 7); });
  _boardMenu->addAction(seven);

  QAction *ten = new QAction("10 x 10", _boardMenu);
  connect(ten, &QAction::triggered, [this]() { this->changeGameSize(10, 10); });
  _boardMenu->addAction(ten);
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

void MainWindow::startNewGame() {
  this->_isGameEnd = false;
  std::string _gameString = "";
  for (uint8_t row = 0; row < _boardHeight; row++) {
    for (uint8_t col = 0; col < _boardWidth; col++) {
      _gameString += ".";
    }
    _gameString += "*";
  }
  _gameString.pop_back();

  if (_game != nullptr) {
    _game = nullptr;
    delete _game;
  }
  _game = new Solver::Game(_gameString);

  // clear UI
  for (auto c : _boardVec) {
    c->setEnabled(true);
    c->setText("");
  }
  this->updateCurrentPlayer(this->_game->to_play);
  _browser->clear();
}

void MainWindow::changeGameSize(uint8_t width, uint8_t height) {
  _isGameEnd = false;
  _boardHeight = height;
  _boardWidth = width;
  std::string _gameString = "";
  for (uint8_t row = 0; row < _boardHeight; row++) {
    for (uint8_t col = 0; col < _boardWidth; col++) {
      _gameString += ".";
    }
    _gameString += "*";
  }
  _gameString.pop_back();

  if (_game != nullptr) {
    _game = nullptr;
    delete _game;
  }
  _game = new Solver::Game(_gameString);

  // redraw & clear UI
  this->clearBoardLayout();
  _boardVec.clear();
  this->drawBoard();
  this->updateCurrentPlayer(this->_game->to_play);
  _browser->clear();
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
  while (_boardLayout->count() > 0) {
    auto item = _boardLayout->itemAt(0)->widget();
    item->deleteLater();
    delete item;
  }
}

void MainWindow::drawBoard() {
  // init board x y axis
  for (uint8_t col = 1; col < _boardWidth + 1; col++) {
    char c = 64 + col;  // ascii 'A' = 65
    QLabel *l = new QLabel(QChar(c));
    l->setAlignment(Qt::AlignCenter);
    _boardLayout->addWidget(l, 0, col, 1, 1);
  }
  for (uint8_t row = 1; row < _boardHeight + 1; row++) {
    _boardLayout->addWidget(new QLabel(uint8ToQstring(row)), row, 0, 1, 1);
  }
  // init board cells
  for (uint8_t row = 0; row < _boardHeight; row++) {
    for (uint8_t col = 0; col < _boardWidth; col++) {
      QString t = "";
      BoardCell *button = new BoardCell(
          t, QPoint(col, row), this);  // note that col=x, row=y, from top down
      _boardVec.push_back(button);
      connect(button, &QPushButton::pressed,
              [button, this]() { this->onBoardCellPressed(button); });
      // offset each cell because of the x-y axis labels
      _boardLayout->addWidget(button, row + 1, col + 1, 1, 1);
    }
  }
}

void MainWindow::updateCurrentPlayer(Solver::PLAYER p) {
  if (p == Solver::PLAYER::BLACK)
    this->_currPlayer->setText("BLACK");
  else
    this->_currPlayer->setText("WHITE");
}

QString MainWindow::getMoveMessage(Solver::Pos p, QString val) {
  QString res = QString::number(this->_moveCounter++) + ". " +
                this->_currPlayer->text() + ": ";
  char c = 65 + p.col;  // 'A' = 65
  res += QChar(c);
  res += uint8ToQstring(p.row + 1);
  res += " - ";
  res += val;
  return res;
}

void MainWindow::playByAI() {
  // TODO: optimization, every time we are creating a new game and a new solver
  if (_dfpnAgent != nullptr) {
    _dfpnAgent = nullptr;
    delete _dfpnAgent;
  }
  _dfpnAgent = new Solver::DFPN(*_game);
  _dfpnAgent->solve();
  Solver::Move nextMove = _dfpnAgent->best_move;
  if (nextMove.value == 0) {  // This may not be reached at all
    qDebug() << "no possible moves";
    return;
  }

  // Play
  this->_game->unsafePlay(nextMove.pos, nextMove.value);

  // GUI update
  BoardCell *cell = nullptr;
  for (auto c : this->_boardVec) {
    if (c->getPos().y() == nextMove.pos.row &&
        c->getPos().x() == nextMove.pos.col) {
      cell = c;
    }
  }
  QString moveValue = uint8ToQstring(nextMove.value);
  cell->setText(moveValue);
  cell->setEnabled(false);
  this->_browser->append(this->getMoveMessage(nextMove.pos, moveValue));
  this->updateCurrentPlayer(this->_game->to_play);

  // Game update
  this->_gameString = this->_game->toString();
  delete this->_game;
  this->_game = new Solver::Game(this->_gameString);
  if (_game->getPossibleMoves().size() == 0) {
    this->_isGameEnd = true;
    QString s = "AI wins!";
    this->displayMessage(s);
  }
}

void MainWindow::displayMessage(QString s) {
  QMessageBox msgBox;
  msgBox.setText(s);
  msgBox.exec();
}

void MainWindow::onBoardCellPressed(BoardCell *cell) {
  if (this->_isGameEnd) {
    QString s = "Game is ended. Please start a new game.";
    this->displayMessage(s);
    return;
  }
  // _mainWidget->setEnabled(false);    // prevent from clicking another cell
  Solver::Pos cellPos = Solver::Pos{static_cast<uint8_t>(cell->getPos().y()),
                                    static_cast<uint8_t>(cell->getPos().x())};

  auto allMoves = _game->getPossibleMoves();
  if (allMoves.find(cellPos) == allMoves.end()) {
    QMessageBox msgBox;
    msgBox.setText("No Possible Move");
    msgBox.exec();
    cell->setEnabled(false);
    return;
  }
  auto moves = allMoves.at(cellPos);

  if (true == _isSelectionFinished) {
    _isSelectionFinished = false;
  } else {
    _popupSelection->deleteLater();
    delete _popupSelection;
  }
  _popupSelection = PopupSelection::GetInstance(moves);
  connect(_popupSelection, &PopupSelection::selectedNumber,
          [cell, cellPos, this](QString moveValue) {
            cell->setText(moveValue);
            this->_game->unsafePlay(cellPos, QStringToUint8(moveValue));
            this->_gameString = this->_game->toString();
            delete this->_game;
            this->_game = new Solver::Game(this->_gameString);

            this->_browser->append(this->getMoveMessage(cellPos, moveValue));
            if (this->_game->getPossibleMoves().size() == 0) {
              // user clicked a dead cell
              _popupSelection->close();
              this->_isGameEnd = true;
              QString s = "Winner: " + this->_currPlayer->text();
              this->displayMessage(s);
            } else {
              // the move was successful
              cell->setEnabled(false);
              this->updateCurrentPlayer(this->_game->to_play);
              _popupSelection->close();
            }
            this->_isSelectionFinished = true;
            if (true == this->_isAI) {
              this->playByAI();
            }
          });
  _popupSelection->move(QCursor::pos());
  _popupSelection->show();
}

}  // namespace GUI