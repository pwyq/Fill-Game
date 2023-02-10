#ifndef FG_GUI_MAIN_WINDOW_H_
#define FG_GUI_MAIN_WINDOW_H_

// Qt includes
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMainWindow>
// #include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QTextBrowser>
#include <QWidget>

#include <iostream>
#include <vector>

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
  void updateCurrentPlayer(Solver::PLAYER player);
  void playByAI();
  void displayMessage(QString s);
  QString getMoveMessage(Solver::Pos pos, QString moveValue);

  // slots
  void onBoardCellPressed(BoardCell *cell);

private:
  Solver::Game *_game = nullptr; // TODO: std::auto_ptr, std::shared_ptr?

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

} // namespace GUI

#endif // FG_GUI_MAIN_WINDOW_H_