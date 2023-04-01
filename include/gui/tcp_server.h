/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 23:11:18
 * @modify date 2023-03-26 03:17:06
 * @desc TCP Server
 * 
 * Each Fill-Game GUI application instance has only one server and only one client.
 * Server is used to only recieve data, client is used to only send data.
 * 
 */

#ifndef FG_GUI_TCP_SERVER_H_
#define FG_GUI_TCP_SERVER_H_

#include <QDebug>
#include <QFileDialog>
#include <QSet>
#include <QTcpServer>
#include <QTcpSocket>

namespace gui {

class TCPServer : public QObject {
  Q_OBJECT

 public:
  explicit TCPServer(QWidget* parent = nullptr);
  ~TCPServer();

  void setup(const QHostAddress& addr, quint16 port);

 signals:
  void newMessage(QString data);
  void clientMessage(QString data);
  void lostConnection();

 private slots:
  void
  newConnection();
  void readSocket();
  void discardSocket();
  void displayMessage(const QString& str);

 private:
  QTcpServer* server_        = nullptr;
  QTcpSocket* target_socket_ = nullptr;
};

}  // namespace gui

#endif