/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-21 21:19:40
 * @modify date 2023-03-23 02:53:29
 * @desc Infomation dock
 */

#ifndef FG_GUI_INFO_DOCK_H_
#define FG_GUI_INFO_DOCK_H_

// std
#include <mutex>
#include <thread>
// Qt
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QTextBrowser>
#include <QTime>
#include <QTimer>

namespace gui {

class InfoDock : public QDockWidget {
  Q_OBJECT
  ///////////// Singleton /////////////
 public:
  InfoDock(InfoDock &other) = delete;         // non-clonable
  void operator=(const InfoDock &) = delete;  // non-assignable
  static InfoDock *GetInstance();
  ~InfoDock();

 protected:
  InfoDock();

 private:
  static InfoDock *pinstance_;
  static std::mutex mutex_;
  /////////////////////////////////////
 public:
  void resetPlayer();
  void updatePlayer();
  inline void setGameTime(uint32_t t) { countdown_ = t; }

  QString getCurrentPlayer();

  QTextBrowser *browser() const { return browser_; }

 protected:
  QGridLayout *layout_;
  QWidget *widget_;
  QLabel *playerW_;
  QLabel *playerB_;
  QLabel *timerW_label_;
  QLabel *timerB_label_;
  QTimer *timerW_;
  QTimer *timerB_;
  QTime timeW_;
  QTime timeB_;
  QTextBrowser *browser_;

  void initUI();
  void resetTimerUI();
  void setCountdownTime();

 private:
  const QString timer_format = "mm:ss";
  uint32_t countdown_        = 10;  // in seconds

  void loadQSS();

 private slots:
  void onWhiteTimeout();
  void onBlackTimeout();

 signals:
  void gameTimeOut(QString s);
};

}  // namespace gui

#endif