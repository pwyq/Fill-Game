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
#include <QWidget>
// std
#include <iostream>
#include <vector>
// local
#include "gui/board_cell.h"
#include "gui/info_dock.h"
#include "gui/input_dialog.h"
#include "gui/popup_selection.h"
#include "solver/dfpn.h"
#include "solver/game.h"

using solver::helper::PLAYER;
using solver::helper::Pos;

namespace gui {

// TODO: singleton
class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();
  // ~MainWindow();   // No need of destructor; otherwise double free(); the rule of 3/5/0
  void initUI();
  void startNewGame();
  void changeGameSize(uint8_t width, uint8_t height);

 protected:
  QHBoxLayout *main_layout_;
  QGridLayout *board_layout_;
  QWidget *main_widget_;

  QMenu *game_menu_;
  QMenu *board_menu_;
  QMenu *help_menu_;
  uint8_t board_width_;
  uint8_t board_height_;
  bool is_AI_ = false;
  std::vector<BoardCell *> board_cells_;

  void initGameMenu();
  void initBoardMenu();
  void initHelpMenu();
  void drawBoard();
  void playByAI();
  inline void displayMessage(QString s);
  inline QString getMoveMessage(Pos pos, QString moveValue);

  // slots
  void onBoardCellPressed(BoardCell *cell);

 private:
  // UI members
  PopupSelection *pop_selection_ = nullptr;
  InfoDock *info_dock_           = nullptr;

  // Solver members
  solver::Game *game_             = nullptr;  // TODO: std::auto_ptr, std::shared_ptr?
  solver::dfpn::DFPN *agent_dfpn_ = nullptr;

  std::string game_string_;

  int move_counter_ = 1;

  bool is_select_done_ = true;
  bool is_game_end_    = false;

  // template<class T>
  // void clearLayout(T* layoutType, bool deleteWidgets);
  void clearBoardLayout();
};

inline QString MainWindow::getMoveMessage(Pos p, QString val) {
  QString res = QString::number(this->move_counter_++) + ". " + this->info_dock_->getCurrentPlayer() + ": ";
  char c      = 65 + p.col;  // 'A' = 65
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

}  // namespace gui

#endif  // FG_GUI_MAIN_WINDOW_H_