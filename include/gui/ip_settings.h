/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-25 02:02:35
 * @modify date 2023-03-25 14:12:01
 * @desc IP Connection Settings
 */

#ifndef FG_GUI_IP_SETTINGS_H_
#define FG_GUI_IP_SETTINGS_H_

// https://doc.qt.io/qt-6/qtwidgets-dialogs-tabdialog-example.html
// std
#include <mutex>
#include <thread>
// Qt
#include <QDialog>
#include <QDialogButtonBox>
#include <QFileInfo>
#include <QHostAddress>
#include <QLabel>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QTabWidget>
// local
#include "gui/helper.h"

namespace gui {

class GeneralTab : public QWidget {
  Q_OBJECT

 public:
  explicit GeneralTab(QWidget *parent = nullptr);

  inline QString myIP() const { return my_ip_->text(); }
  inline QString myPort() const;
  inline QString targetIP() const;
  inline QString targetPort() const;

 private:
  QLabel *my_ip_;  // this machine's ip
  QLineEdit *my_port_;
  QLineEdit *ip_edit_;    // opponent ip (i.e. target ip)
  QLineEdit *port_edit_;  // opponent port
  QRegularExpressionValidator *ip_validator_;

  const QHostAddress
  getAddress();
};

inline QString GeneralTab::myPort() const {
  return my_port_->displayText() == "" ? my_port_->placeholderText() : my_port_->displayText();
}

inline QString GeneralTab::targetIP() const {
  return ip_edit_->displayText() == "" ? ip_edit_->placeholderText() : ip_edit_->displayText();
}
inline QString GeneralTab::targetPort() const {
  return port_edit_->displayText() == "" ? port_edit_->placeholderText() : port_edit_->displayText();
}

/*
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
*/

class IPSettingDialog : public QDialog {
  Q_OBJECT

  ///////////// Singleton /////////////
 public:
  IPSettingDialog(IPSettingDialog &other) = delete;  // non-clonable
  void operator=(const IPSettingDialog &) = delete;  // non-assignable
  static IPSettingDialog *GetInstance(const QString &fileName, QWidget *parent = nullptr);
  ~IPSettingDialog();

 protected:
  explicit IPSettingDialog(const QString &fileName, QWidget *parent = nullptr);

 private:
  static IPSettingDialog *pinstance_;
  static std::mutex mutex_;
  /////////////////////////////////////

 private slots:
  void onAccept();

 private:
  QTabWidget *tabWidget;
  QDialogButtonBox *buttonBox;

  GeneralTab *tab_general_;
 signals:
  void confirmIPs(QStringList str_list);
};

}  // namespace gui

#endif