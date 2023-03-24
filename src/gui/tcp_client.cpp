/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 23:12:40
 * @modify date 2023-03-24 01:22:19
 */

#include "gui/tcp_client.h"

namespace gui {

TCPClient::TCPClient(QWidget* parent) {
  socket = new QTcpSocket(this);

  connect(this, &TCPClient::newMessage, this, &TCPClient::displayMessage);
  connect(socket, &QTcpSocket::readyRead, this, &TCPClient::readSocket);
  connect(socket, &QTcpSocket::disconnected, this, &TCPClient::discardSocket);

  socket->connectToHost(QHostAddress::LocalHost, 8080);

  if (socket->waitForConnected())
    qDebug() << "Connected to Server";
  else {
    qDebug() << QString("QTCPClient - The following error occurred: %1.").arg(socket->errorString());
    exit(EXIT_FAILURE);
  }
}

TCPClient::~TCPClient() {
  if (socket->isOpen())
    socket->close();
}

void TCPClient::readSocket() {
  QByteArray buffer;

  QDataStream socketStream(socket);
  socketStream.setVersion(QDataStream::Qt_5_12);

  socketStream.startTransaction();
  socketStream >> buffer;

  if (!socketStream.commitTransaction()) {
    QString message = QString("%1 :: Waiting for more data to come..").arg(socket->socketDescriptor());
    emit newMessage(message);
    return;
  }

  QString header   = buffer.mid(0, 128);
  QString fileType = header.split(",")[0].split(":")[1];

  buffer = buffer.mid(128);

  if (fileType == "message") {
    QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
    emit newMessage(message);
  }
}

void TCPClient::discardSocket() {
  socket->deleteLater();
  socket = nullptr;

  qDebug() << ("Disconnected!");
}

void TCPClient::displayMessage(const QString& str) {
  qDebug() << "client!!";
  qDebug() << str;
}

}  // namespace gui
