/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 23:12:35
 * @modify date 2023-03-25 02:23:37
 */

#include "gui/tcp_server.h"

namespace gui {

TCPServer::TCPServer(QWidget* parent) {
  server_ = new QTcpServer();
}

TCPServer::~TCPServer() {
  if (target_socket_ != nullptr && target_socket_->isOpen()) {
    target_socket_->close();
    target_socket_->deleteLater();
    target_socket_ = nullptr;
  }

  server_->close();
  server_->deleteLater();
  server_ = nullptr;
}

void TCPServer::setup(const QHostAddress& addr, quint16 port) {
  if (server_->listen(addr, port)) {
    connect(this, &TCPServer::newMessage, this, &TCPServer::displayMessage);
    connect(server_, &QTcpServer::newConnection, this, &TCPServer::newConnection);
  } else {
    qDebug() << QString("Unable to start the server: %1.").arg(server_->errorString());
    exit(EXIT_FAILURE);
  }
}

void TCPServer::newConnection() {
  if (target_socket_ != nullptr && target_socket_->isValid()) {
    qDebug() << "server: already connected to a player";
    return;
  }
  target_socket_ = server_->nextPendingConnection();
  connect(target_socket_, &QTcpSocket::readyRead, this, &TCPServer::readSocket);
  connect(target_socket_, &QTcpSocket::disconnected, this, &TCPServer::discardSocket);
  qDebug() << QString::number(target_socket_->socketDescriptor());
  displayMessage(QString("INFO :: Client with sockd:%1 has just entered the room").arg(target_socket_->socketDescriptor()));
}

void TCPServer::readSocket() {
  QByteArray buffer;

  QDataStream socketStream(target_socket_);
  socketStream.setVersion(QDataStream::Qt_5_12);

  socketStream.startTransaction();
  socketStream >> buffer;

  if (!socketStream.commitTransaction()) {
    // QString message = QString("%1 :: Waiting for more data to come..").arg(socket->socketDescriptor());
    // emit newMessage(message);
    return;
  }

  QString header   = buffer.mid(0, 128);
  QString fileType = header.split(",")[0].split(":")[1];

  buffer = buffer.mid(128);

  if (fileType == "message") {
    QString message = QString("%1 :: %2").arg(target_socket_->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
    emit newMessage(message);
  }
}

void TCPServer::discardSocket() {
  target_socket_->deleteLater();
  target_socket_ = nullptr;
  qDebug() << ("server: Disconnected!");
}

void TCPServer::sendMessage(const QString& msg) {
  if (target_socket_ == nullptr) {
    qDebug() << "QTCPServer - Not connected";
    return;
  }
  if (false == target_socket_->isOpen()) {
    qDebug() << "QTCPServer - Socket doesn't seem to be opened";
    return;
  }

  QDataStream socketStream(target_socket_);
  socketStream.setVersion(QDataStream::Qt_5_12);

  QByteArray header;
  header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(msg.size()).toUtf8());
  header.resize(128);

  QByteArray byteArray = msg.toUtf8();
  byteArray.prepend(header);

  socketStream.setVersion(QDataStream::Qt_5_12);
  socketStream << byteArray;
}

void TCPServer::displayMessage(const QString& str) {
  qDebug() << "server!! " << str;
}

}  // namespace gui