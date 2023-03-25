/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 23:12:07
 * @modify date 2023-03-24 01:22:15
 * @desc TCP Client
 */
#ifndef FG_GUI_TCP_CLIENT_H_
#define FG_GUI_TCP_CLIENT_H_

#include <QAbstractSocket>
#include <QDebug>
#include <QFileDialog>
#include <QHostAddress>
#include <QString>
#include <QTcpSocket>

namespace gui {

class TCPClient : public QObject {
  Q_OBJECT

 public:
  explicit TCPClient(QWidget* parent = nullptr);
  ~TCPClient();
  void sendMessage();
 signals:
  void newMessage(QString);
 private slots:
  void readSocket();
  void discardSocket();
  void displayMessage(const QString& str);

 private:
  QTcpSocket* socket_ = nullptr;
};

}  // namespace gui

#endif