/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 17:04:59
 * @modify date 2023-03-24 01:24:30
 */

#include "gui/main_window_menu_bar.h"
// Qt
#include <QApplication>
#include <QDebug>
// local
#include "gui/input_dialog.h"
#include "gui/popup_window.h"

namespace gui {

///////////// Singleton /////////////
MainWindowMenuBar *MainWindowMenuBar::pinstance_{nullptr};
std::mutex MainWindowMenuBar::mutex_;

MainWindowMenuBar::MainWindowMenuBar(QWidget *parent) : QMenuBar(parent) {
  game_menu_     = this->addMenu("&Game");
  opponent_menu_ = this->addMenu("&Opponent");
  board_menu_    = this->addMenu("&Board");
  help_menu_     = this->addMenu("&Help");

  this->initGameMenu();
  this->initOpponentMenu();
  this->initBoardMenu();
  this->initHelpMenu();
}

MainWindowMenuBar::~MainWindowMenuBar() { pinstance_ = nullptr; }

MainWindowMenuBar *MainWindowMenuBar::GetInstance(QWidget *parent) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (pinstance_ == nullptr) {
    pinstance_ = new MainWindowMenuBar(parent);
  }
  return pinstance_;
}
/////////////////////////////////////

void MainWindowMenuBar::initGameMenu() {
  QAction *startNewGame = new QAction("Start &New Game", game_menu_);
  connect(startNewGame, &QAction::triggered, [this]() {
    emit this->startNewGame();
  });
  game_menu_->addAction(startNewGame);

  game_menu_->addSeparator();

  QAction *settings = new QAction("&Settings", game_menu_);
  connect(settings, &QAction::triggered, [this]() {
    emit this->openSettings();
  });
  game_menu_->addAction(settings);

  game_menu_->addSeparator();

  QAction *quit = new QAction("&Quit", game_menu_);
  connect(quit, &QAction::triggered, [this]() {
    this->close();
  });
  game_menu_->addAction(quit);
}

void MainWindowMenuBar::initOpponentMenu() {
  QAction *dfpn = new QAction("DFPN", opponent_menu_);
  connect(dfpn, &QAction::triggered, [this]() {
    emit this->selectOpponent(helper::SOLVER::DFPN);
  });
  opponent_menu_->addAction(dfpn);

  QAction *pns = new QAction("PNS (TODO)", opponent_menu_);
  connect(pns, &QAction::triggered, [this]() {
    emit this->selectOpponent(helper::SOLVER::PNS);
  });
  opponent_menu_->addAction(pns);

  QAction *minimax = new QAction("Minimax + AB + TT (TODO)", opponent_menu_);
  connect(minimax, &QAction::triggered, [this]() {
    emit this->selectOpponent(helper::SOLVER::MINIMAX_AB_TT);
  });
  opponent_menu_->addAction(minimax);

  QAction *negamax = new QAction("Negamax + AB + TT (TODO)", opponent_menu_);
  connect(negamax, &QAction::triggered, [this]() {
    emit this->selectOpponent(helper::SOLVER::NEGAMAX_AB_TT);
  });
  opponent_menu_->addAction(negamax);

  opponent_menu_->addSeparator();

  QAction *human_remote = new QAction("Human vs Human (remote)", opponent_menu_);
  connect(human_remote, &QAction::triggered, [this]() {
    emit this->selectOpponent(helper::SOLVER::HUMAN_REMOTE);
  });
  opponent_menu_->addAction(human_remote);

  QAction *human_local = new QAction("Human vs Human (local)", opponent_menu_);
  connect(human_local, &QAction::triggered, [this]() {
    emit this->selectOpponent(helper::SOLVER::HUMAN_LOCAL);
  });
  opponent_menu_->addAction(human_local);
}

void MainWindowMenuBar::initBoardMenu() {
  QAction *three = new QAction("3 x 3", board_menu_);
  connect(three, &QAction::triggered, [this]() {
    emit this->changeGameSize(3, 3);
  });
  board_menu_->addAction(three);

  QAction *five = new QAction("5 x 5", board_menu_);
  connect(five, &QAction::triggered, [this]() {
    emit this->changeGameSize(5, 5);
  });
  board_menu_->addAction(five);

  QAction *seven = new QAction("7 x 7", board_menu_);
  connect(seven, &QAction::triggered, [this]() {
    emit this->changeGameSize(7, 7);
  });
  board_menu_->addAction(seven);

  QAction *ten = new QAction("10 x 10", board_menu_);
  connect(ten, &QAction::triggered, [this]() {
    emit this->changeGameSize(10, 10);
  });
  board_menu_->addAction(ten);

  QAction *custom = new QAction("&Custom Board Size", board_menu_);
  connect(custom, &QAction::triggered, [this]() {
    // QStringList list = InputDialog::getStrings(this);
    // if (!list.isEmpty()) {
    // use list
    // }
    std::pair<uint8_t, uint8_t> res = InputDialog::getInputs(this);
    emit this->changeGameSize(res.first, res.second);
  });
  board_menu_->addAction(custom);
}

void MainWindowMenuBar::initHelpMenu() {
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

}  // namespace gui
