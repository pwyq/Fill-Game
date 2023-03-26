/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 23:12:40
 * @modify date 2023-03-25 01:12:03
 */

#include "gui/tcp_client.h"

namespace gui {

TCPClient::TCPClient(QWidget* parent) {
  socket_ = new QTcpSocket(this);
}

TCPClient::~TCPClient() {
  if (socket_ != nullptr && socket_->isOpen()) {
    socket_->close();
    socket_->deleteLater();  // TODO: do we need this?
    socket_ = nullptr;
  }
}

void TCPClient::setup(const QHostAddress& addr, quint16 port) {
  connect(this, &TCPClient::newMessage, this, &TCPClient::displayMessage);
  connect(socket_, &QTcpSocket::readyRead, this, &TCPClient::readSocket);
  connect(socket_, &QTcpSocket::disconnected, this, &TCPClient::discardSocket);

  socket_->connectToHost(addr, port);

  if (socket_->waitForConnected()) {
    qDebug() << "Connected to Server";
  } else {
    qDebug() << QString("QTCPClient - The following error occurred: %1.").arg(socket_->errorString());
    exit(EXIT_FAILURE);
  }
}

void TCPClient::readSocket() {
  QByteArray buffer;

  QDataStream socketStream(socket_);
  socketStream.setVersion(QDataStream::Qt_5_12);

  socketStream.startTransaction();
  socketStream >> buffer;

  if (!socketStream.commitTransaction()) {
    QString message = QString("%1 :: Waiting for more data to come..").arg(socket_->socketDescriptor());
    emit newMessage(message);
    return;
  }

  QString header   = buffer.mid(0, 128);
  QString fileType = header.split(",")[0].split(":")[1];

  buffer = buffer.mid(128);

  if (fileType == "message") {
    QString message = QString("%1 :: %2").arg(socket_->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
    emit newMessage(message);
  }
}

void TCPClient::discardSocket() {
  socket_->deleteLater();
  socket_ = nullptr;

  qDebug() << ("client: Disconnected!");
}

void TCPClient::sendMessage(const QString& msg) {
  if (socket_ == nullptr) {
    qDebug() << "QTCPServer - Not connected";
    return;
  }
  if (false == socket_->isOpen()) {
    qDebug() << "QTCPServer - Socket doesn't seem to be opened";
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

void TCPClient::displayMessage(const QString& str) {
  qDebug() << "client!! " << str;
}

}  // namespace gui
