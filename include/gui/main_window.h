/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:27:13
 * @modify date 2023-03-31 18:05:58
 * @desc GUI's Main window, including title bar, menu bar, game board, info
 * panel
 */
#ifndef FG_GUI_MAIN_WINDOW_H_
#define FG_GUI_MAIN_WINDOW_H_

// std
#include <iostream>
#include <vector>
// Qt
#include <QDebug>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
// local
#include "gui/board_cell.h"
#include "gui/helper.h"
#include "gui/info_dock.h"
#include "gui/ip_settings.h"
#include "gui/main_window_menu_bar.h"
#include "gui/new_game_window.h"
#include "gui/popup_selection.h"
#include "gui/tcp_client.h"
#include "gui/tcp_server.h"
#include "gui/worker.h"
#include "solver/game.h"

using solver::helper::PLAYER;
using solver::helper::Pos;

namespace gui {

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();
  // ~MainWindow();  // No need of destructor; otherwise double free(); the rule of 3/5/0

 private:
  // UI members
  MainWindowMenuBar *menu_bar_    = nullptr;
  InfoDock *info_dock_            = nullptr;
  PopupSelection *pop_selection_  = nullptr;
  IPSettingDialog *ip_settings_   = nullptr;
  NewGameWindow *new_game_window_ = nullptr;
  QHBoxLayout *main_layout_;
  QGridLayout *board_layout_;
  QWidget *main_widget_;

  uint8_t board_width_;
  uint8_t board_height_;
  std::vector<BoardCell *> board_cells_;
  PLAYER gui_player_ = PLAYER::BLACK;

  // Solver members
  solver::Game *game_    = nullptr;  // TODO: std::auto_ptr, std::shared_ptr?
  helper::SOLVER solver_ = helper::SOLVER::DFPN;
  uint32_t move_counter_ = 1;  // BLACK always play the odd number of round
  std::string game_string_;
  bool is_AI_            = false;
  bool is_game_end_      = false;
  bool is_opponent_turn_ = false;
  bool is_select_done_   = true;

  // TCP
  TCPServer *tcp_server_;
  TCPClient *tcp_client_;

  void initUI();
  void clearBoardLayout();
  void drawBoard();
  void playByAI();
  void solverController();
  void startNewGame();
  void playAndUpdate(solver::helper::Move next_move);
  inline QString getMoveMessage(Pos pos, QString moveValue);
 private slots:
  void onBoardCellPressed(BoardCell *cell);
  void onClientMessageReceived(QString data);
  void onNewGameRequested();
  void onOpponentSelected(helper::SOLVER opponent);
  void onPlayerColorSelected(PLAYER color);
  void onSettingsOpened();
  void onSolverFinished(solver::helper::Move move);
  void onTargetIPConfirmed(QStringList str_list);
  void changeGameSize(uint8_t width, uint8_t height);

 signals:
  void stopGameTimer();
};

inline QString MainWindow::getMoveMessage(Pos p, QString val) {
  QString res = QString::number(this->move_counter_++) + ". " + this->info_dock_->getCurrentPlayer() + ": ";
  char c      = 65 + p.col;  // 'A' = 65
  res += QChar(c);
  res += helper::uint8ToQstring(p.row + 1);
  res += " - ";
  res += val;
  return res;
}

}  // namespace gui

// For Qt slots/signals
//  This must be placed after the class decalaration and outside the namespace
Q_DECLARE_METATYPE(solver::helper::Move)

#endif  // FG_GUI_MAIN_WINDOW_H_