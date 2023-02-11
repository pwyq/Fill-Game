/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-11 11:11:53
 * @modify date 2023-02-11 11:56:22
 * @desc Custom QMainWindow for popup window template
 */
#ifndef FG_GUI_POPUP_WINDOW_H_
#define FG_GUI_POPUP_WINDOW_H_

// Qt
#include <QDesktopWidget>
#include <QGridLayout>
#include <QMainWindow>
#include <QTextBrowser>
#include <QWidget>

namespace gui {

class PopupWindow : public QMainWindow {
  Q_OBJECT
 public:
  PopupWindow(const QString& title, const QString& htmlPath);
  ~PopupWindow();
  inline void setWindowSize(const float& widthRatio, const float& heightRatio);

 protected:
  QGridLayout* layout_;
  QWidget* widget_;
  QTextBrowser* browser_;

  void initUI(const QString& title, const QString& htmlPath);
};

inline void PopupWindow::setWindowSize(const float& widthRatio, const float& heightRatio) {
  assert(0 <= widthRatio && widthRatio < 1);
  assert(0 <= heightRatio && heightRatio < 1);
  QDesktopWidget dw;
  float ww = widthRatio * dw.availableGeometry().width();
  float hh = heightRatio * dw.availableGeometry().height();
  this->setFixedSize(QSize(ww, hh));
}

}  // namespace gui

#endif