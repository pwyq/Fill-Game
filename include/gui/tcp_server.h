/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 23:11:18
 * @modify date 2023-03-24 01:22:17
 * @desc TCP Server
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

  void sendMessage();

 signals:
  void newMessage(QString);
 private slots:
  void newConnection();
  void appendToSocketList(QTcpSocket* socket);

  void readSocket();
  void discardSocket();

  void displayMessage(const QString& str);
  void sendMessage(QTcpSocket* socket);
  void sendAttachment(QTcpSocket* socket, QString filePath);

 private:
  QTcpServer* m_server;
  QSet<QTcpSocket*> connection_set;
};

}  // namespace gui

#endif