/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 17:04:46
 * @modify date 2023-03-23 17:04:54
 * @desc Main Window Menu Bar
 */

#ifndef FG_GUI_MAIN_WINDOW_MENU_BAR_H_
#define FG_GUI_MAIN_WINDOW_MENU_BAR_H_

// std
#include <mutex>
#include <thread>
// Qt
#include <QMenu>
#include <QMenuBar>
// local
#include "gui/helper.h"

namespace gui {
class MainWindowMenuBar : public QMenuBar {
  Q_OBJECT
  ///////////// Singleton /////////////
 public:
  MainWindowMenuBar(MainWindowMenuBar &other) = delete;  // non-clonable
  void operator=(const MainWindowMenuBar &) = delete;    // non-assignable
  static MainWindowMenuBar *GetInstance(QWidget *parent = nullptr);
  ~MainWindowMenuBar();

 protected:
  MainWindowMenuBar(QWidget *parent = nullptr);

 private:
  static MainWindowMenuBar *pinstance_;
  static std::mutex mutex_;
  /////////////////////////////////////

 private:
  QMenu *game_menu_;
  QMenu *opponent_menu_;
  QMenu *board_menu_;
  QMenu *help_menu_;

  void initGameMenu();
  void initOpponentMenu();
  void initBoardMenu();
  void initHelpMenu();
 signals:
  void selectOpponent(helper::SOLVER opponent);
  void startNewGame();
  void changeGameSize(uint8_t width, uint8_t height);
};

}  // namespace gui

#endif