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

using solver::helper::PLAYER;
using solver::helper::Pos;

namespace gui {

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
  QHBoxLayout *main_layout_;
  QGridLayout *board_layout_;
  QGridLayout *info_layout_;
  QWidget *main_widget_;
  QLabel *curr_player_label_;
  QTextBrowser *browser_;

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
  inline void updateCurrentPlayer(PLAYER player);
  inline void displayMessage(QString s);
  inline QString getMoveMessage(Pos pos, QString moveValue);

  // slots
  void onBoardCellPressed(BoardCell *cell);

 private:
  solver::Game *game_ = nullptr;  // TODO: std::auto_ptr, std::shared_ptr?

  PopupSelection *pop_selection_  = nullptr;
  solver::dfpn::DFPN *agent_dfpn_ = nullptr;

  std::string game_string_;

  int move_counter_ = 1;

  bool is_select_done_ = true;
  bool is_game_end_    = false;

  // template<class T>
  // void clearLayout(T* layoutType, bool deleteWidgets);
  void clearBoardLayout();
};

// inline function declaration
inline void MainWindow::updateCurrentPlayer(PLAYER p) {
  if (p == PLAYER::BLACK)
    this->curr_player_label_->setText("BLACK");
  else
    this->curr_player_label_->setText("WHITE");
}

inline QString MainWindow::getMoveMessage(Pos p, QString val) {
  QString res = QString::number(this->move_counter_++) + ". " +
                this->curr_player_label_->text() + ": ";
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

}  // namespace gui

#endif  // FG_GUI_MAIN_WINDOW_H_