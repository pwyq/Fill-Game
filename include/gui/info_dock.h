/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-21 21:19:40
 * @modify date 2023-03-23 00:30:10
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
  QString getCurrentPlayer();
  QTextBrowser *browser() const { return browser_; }

 protected:
  QGridLayout *layout_;
  QWidget *widget_;
  QLabel *playerW_;
  QLabel *playerB_;
  QTextBrowser *browser_;

  void initUI();
};

}  // namespace gui

#endif