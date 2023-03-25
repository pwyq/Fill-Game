/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-25 02:02:35
 * @modify date 2023-03-25 02:23:24
 * @desc Setting Tabs
 */

#ifndef FG_GUI_SETTINGS_H_
#define FG_GUI_SETTINGS_H_

// https://doc.qt.io/qt-6/qtwidgets-dialogs-tabdialog-example.html
// std
#include <mutex>
#include <thread>
// Qt
#include <QDialog>
#include <QDialogButtonBox>
#include <QFileInfo>
#include <QTabWidget>

namespace gui {

class GeneralTab : public QWidget {
  Q_OBJECT

 public:
  explicit GeneralTab(const QFileInfo &fileInfo, QWidget *parent = nullptr);
};

class PermissionsTab : public QWidget {
  Q_OBJECT

 public:
  explicit PermissionsTab(const QFileInfo &fileInfo, QWidget *parent = nullptr);
};

class ApplicationsTab : public QWidget {
  Q_OBJECT

 public:
  explicit ApplicationsTab(const QFileInfo &fileInfo, QWidget *parent = nullptr);
};

class TabDialog : public QDialog {
  Q_OBJECT

  ///////////// Singleton /////////////
 public:
  TabDialog(TabDialog &other) = delete;        // non-clonable
  void operator=(const TabDialog &) = delete;  // non-assignable
  static TabDialog *GetInstance(const QString &fileName, QWidget *parent = nullptr);
  ~TabDialog();

 protected:
  explicit TabDialog(const QString &fileName, QWidget *parent = nullptr);

 private:
  static TabDialog *pinstance_;
  static std::mutex mutex_;
  /////////////////////////////////////

 private:
  QTabWidget *tabWidget;
  QDialogButtonBox *buttonBox;
};

}  // namespace gui

#endif