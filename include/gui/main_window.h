/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:27:13
 * @modify date 2023-02-10 05:27:13
 * @desc GUI's Main window, including title bar, menu bar, game board, info
 * panel
 */
#ifndef FG_GUI_MAIN_WINDOW_H_
#define FG_GUI_MAIN_WINDOW_H_

// Qt
#include <QDebug>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QTextBrowser>
#include <QWidget>
// std
#include <iostream>
#include <vector>
// local
#include "gui/board_cell.h"
#include "gui/input_dialog.h"
#include "gui/popup_selection.h"
#include "solver/dfpn.h"
#include "solver/game.h"

namespace GUI {

// TODO: singleton
class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();
  // ~MainWindow();   // No need of destructor; otherwise double free(); the
  // rule of 3/5/0
  void initUI();
  void startNewGame();
  void changeGameSize(uint8_t width, uint8_t height);

 protected:
  QHBoxLayout *_mainLayout;
  QGridLayout *_boardLayout;
  QGridLayout *_infoLayout;
  QWidget *_mainWidget;
  QLabel *_currPlayer;
  QTextBrowser *_browser;

  QMenu *_gameMenu;
  QMenu *_boardMenu;
  uint8_t _boardWidth;
  uint8_t _boardHeight;
  bool _isAI = false;
  std::vector<BoardCell *> _boardVec;

  void initGameMenu();
  void initBoardMenu();
  void drawBoard();
  void playByAI();
  inline void updateCurrentPlayer(Solver::PLAYER player);
  inline void displayMessage(QString s);
  inline QString getMoveMessage(Solver::Pos pos, QString moveValue);

  // slots
  void onBoardCellPressed(BoardCell *cell);

 private:
  Solver::Game *_game = nullptr;  // TODO: std::auto_ptr, std::shared_ptr?

  PopupSelection *_popupSelection = nullptr;
  Solver::DFPN *_dfpnAgent = nullptr;

  std::string _gameString;

  int _moveCounter = 1;

  bool _isSelectionFinished = true;
  bool _isGameEnd = false;

  // template<class T>
  // void clearLayout(T* layoutType, bool deleteWidgets);
  void clearBoardLayout();
};

// inline function declaration
inline void MainWindow::updateCurrentPlayer(Solver::PLAYER p) {
  if (p == Solver::PLAYER::BLACK)
    this->_currPlayer->setText("BLACK");
  else
    this->_currPlayer->setText("WHITE");
}

inline QString MainWindow::getMoveMessage(Solver::Pos p, QString val) {
  QString res = QString::number(this->_moveCounter++) + ". " +
                this->_currPlayer->text() + ": ";
  char c = 65 + p.col;  // 'A' = 65
  res += QChar(c);
  res += uint8ToQstring(p.row + 1);
  res += " - ";
  res += val;
  return res;
}

inline void MainWindow::displayMessage(QString s) {
  QMessageBox msgBox;
  msgBox.setText(s);
  msgBox.exec();
}

}  // namespace GUI

#endif  // FG_GUI_MAIN_WINDOW_H_