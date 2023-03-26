/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 23:12:40
 * @modify date 2023-03-26 02:51:40
 * 
 * TODO: reconnect if lost connection
 */

#include "gui/tcp_client.h"

namespace gui {

TCPClient::TCPClient(QWidget* parent) {
  socket_ = new QTcpSocket(this);
  connect(socket_, &QTcpSocket::disconnected, this, &TCPClient::discardSocket);
}

TCPClient::~TCPClient() {
  if (socket_ != nullptr && socket_->isOpen()) {
    socket_->close();
    socket_->deleteLater();  // TODO: do we need this?
    socket_ = nullptr;
  }
}

void TCPClient::setup(const QHostAddress& addr, quint16 port) {
  socket_->connectToHost(addr, port);

  if (socket_->waitForConnected(5000)) {
    qDebug() << "Connected to Server";
  } else {
    qDebug() << QString("QTCPClient - The following error occurred: %1.").arg(socket_->errorString());
    // exit(EXIT_FAILURE);
    QMetaObject::invokeMethod(
        this, [this, addr, port]() {
          this->setup(addr, port);
        },
        Qt::QueuedConnection);
  }
}

void TCPClient::discardSocket() {
  socket_->deleteLater();
  socket_ = nullptr;

  qDebug() << ("client: Disconnected!");
}

void TCPClient::sendMessage(const QString& msg) {
  if (socket_ == nullptr) {
    qDebug() << "client - Not connected";
    return;
  }
  if (false == socket_->isOpen()) {
    qDebug() << "client - Socket doesn't seem to be opened";
    return;
  }

  QDataStream socketStream(socket_);
  socketStream.setVersion(QDataStream::Qt_5_12);

  QByteArray header;
  header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(msg.size()).toUtf8());
  header.resize(128);

  QByteArray byteArray = msg.toUtf8();
  byteArray.prepend(header);

  socketStream.setVersion(QDataStream::Qt_5_12);
  socketStream << byteArray;
}

/*
void TCPClient::displayMessage(const QString& str) {
  qDebug() << "client!! " << str;
}
*/

}  // namespace gui
