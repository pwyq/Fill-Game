/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 23:12:07
 * @modify date 2023-03-26 03:16:47
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

  void setup(const QHostAddress& addr, quint16 port);
  void sendMessage(const QString& msg);

 private slots:
  void discardSocket();

 private:
  QTcpSocket* socket_ = nullptr;
};

}  // namespace gui

#endif