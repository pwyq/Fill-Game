/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-26 13:10:11
 * @modify date 2023-03-31 16:06:20
 * @desc Start a new game
 */

#ifndef FG_GUI_NEW_GAME_WINDOW_H_
#define FG_GUI_NEW_GAME_WINDOW_H_

// std
#include <mutex>
#include <thread>
// Qt
#include <QButtonGroup>
#include <QDebug>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
// local
#include "gui/helper.h"
#include "solver/helper.h"

using solver::helper::PLAYER;

namespace gui {
class NewGameWindow : public QMainWindow {
  Q_OBJECT
  ///////////// Singleton /////////////
 public:
  NewGameWindow(NewGameWindow &other) = delete;    // non-clonable
  void operator=(const NewGameWindow &) = delete;  // non-assignable
  static NewGameWindow *GetInstance();
  ~NewGameWindow();

 protected:
  NewGameWindow();

 private:
  static NewGameWindow *pinstance_;
  static std::mutex mutex_;
  /////////////////////////////////////

 private:
  QGridLayout *layout_;
  QWidget *widget_;
  QButtonGroup *size_group_;      // board size
  QButtonGroup *opponent_group_;  // AI type / Human
  QButtonGroup *value_group_;     // board value
  QButtonGroup *color_group_;     // black / white / random

  void initUI();
  void initDefaultConfiguration();
  QPushButton *createPushButton(QString name, bool is_enabled = true);
  inline void setWindowSize(const float &widthRatio, const float &heightRatio);
 private slots:
  void onSizeGroupClicked(int id);
  void onOpponentGroupClicked(int id);
  void onValueGroupClicked(int id);
  void onColorGroupClicked(int id);
 signals:
  void changeGameSize(uint8_t width, uint8_t height);
  void selectOpponent(helper::SOLVER opponent);
  void selectPlayerColor(PLAYER color);
};

inline void NewGameWindow::setWindowSize(const float &widthRatio, const float &heightRatio) {
  assert(0 <= widthRatio && widthRatio < 1);
  assert(0 <= heightRatio && heightRatio < 1);
  QDesktopWidget dw;
  float ww = widthRatio * dw.availableGeometry().width();
  float hh = heightRatio * dw.availableGeometry().height();
  this->setFixedSize(QSize(ww, hh));
}

}  // namespace gui

#endif