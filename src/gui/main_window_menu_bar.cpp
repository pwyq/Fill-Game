/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 17:04:59
 * @modify date 2023-04-01 16:52:33
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
  game_menu_ = this->addMenu("&Game");
  help_menu_ = this->addMenu("&Help");

  this->initGameMenu();
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

  QAction *startLastGame = new QAction("Start Last Game", game_menu_);
  connect(startLastGame, &QAction::triggered, [this]() {
    emit this->startLastGame();
  });
  game_menu_->addAction(startLastGame);

  game_menu_->addSeparator();
  /*
  QAction *settings = new QAction("&Settings", game_menu_);
  connect(settings, &QAction::triggered, [this]() {
    emit this->openSettings();
  });
  game_menu_->addAction(settings);

  game_menu_->addSeparator();
  */

  QAction *quit = new QAction("&Quit", game_menu_);
  connect(quit, &QAction::triggered, [this]() {
    QCoreApplication::quit();
  });
  game_menu_->addAction(quit);
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
