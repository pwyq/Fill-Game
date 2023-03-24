/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-23 23:12:35
 * @modify date 2023-03-24 01:22:14
 */

#include "gui/tcp_server.h"

namespace gui {

TCPServer::TCPServer(QWidget* parent) {
  m_server = new QTcpServer();

  if (m_server->listen(QHostAddress::Any, 8080)) {
    connect(this, &TCPServer::newMessage, this, &TCPServer::displayMessage);
    connect(m_server, &QTcpServer::newConnection, this, &TCPServer::newConnection);
  } else {
    qDebug() << QString("Unable to start the server: %1.").arg(m_server->errorString());
    exit(EXIT_FAILURE);
  }
}

TCPServer::~TCPServer() {
  foreach (QTcpSocket* socket, connection_set) {
    socket->close();
    socket->deleteLater();
  }

  m_server->close();
  m_server->deleteLater();
}

void TCPServer::newConnection() {
  while (m_server->hasPendingConnections())
    appendToSocketList(m_server->nextPendingConnection());
}

void TCPServer::appendToSocketList(QTcpSocket* socket) {
  connection_set.insert(socket);
  connect(socket, &QTcpSocket::readyRead, this, &TCPServer::readSocket);
  connect(socket, &QTcpSocket::disconnected, this, &TCPServer::discardSocket);
  qDebug() << QString::number(socket->socketDescriptor());
  displayMessage(QString("INFO :: Client with sockd:%1 has just entered the room").arg(socket->socketDescriptor()));
}

void TCPServer::readSocket() {
  QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

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

void TCPServer::discardSocket() {
  QTcpSocket* socket             = reinterpret_cast<QTcpSocket*>(sender());
  QSet<QTcpSocket*>::iterator it = connection_set.find(socket);
  if (it != connection_set.end()) {
    displayMessage(QString("INFO :: A client has just left the room").arg(socket->socketDescriptor()));
    connection_set.remove(*it);
  }

  socket->deleteLater();
}

void TCPServer::sendMessage() {
  foreach (QTcpSocket* socket, connection_set) {
    sendMessage(socket);
  }
}

void TCPServer::sendMessage(QTcpSocket* socket) {
  if (socket) {
    if (socket->isOpen()) {
      QString str = "ranasdfsadfasdfasfafdssadf";

      QDataStream socketStream(socket);
      socketStream.setVersion(QDataStream::Qt_5_12);

      QByteArray header;
      header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
      header.resize(128);

      QByteArray byteArray = str.toUtf8();
      byteArray.prepend(header);

      socketStream.setVersion(QDataStream::Qt_5_12);
      socketStream << byteArray;
    } else
      qDebug() << "QTCPServer - Socket doesn't seem to be opened";
  } else
    qDebug() << "QTCPServer - Not connected";
}

void TCPServer::sendAttachment(QTcpSocket* socket, QString filePath) {
  if (socket) {
    if (socket->isOpen()) {
      QFile m_file(filePath);
      if (m_file.open(QIODevice::ReadOnly)) {
        QFileInfo fileInfo(m_file.fileName());
        QString fileName(fileInfo.fileName());

        QDataStream socketStream(socket);
        socketStream.setVersion(QDataStream::Qt_5_12);

        QByteArray header;
        header.prepend(QString("fileType:attachment,fileName:%1,fileSize:%2;").arg(fileName).arg(m_file.size()).toUtf8());
        header.resize(128);

        QByteArray byteArray = m_file.readAll();
        byteArray.prepend(header);

        socketStream << byteArray;
      } else
        qDebug() << "QTCPClient - Couldn't open the attachment!";
    } else
      qDebug() << "QTCPServer - Socket doesn't seem to be opened";
  } else
    qDebug() << "QTCPServer - Not connected";
}

void TCPServer::displayMessage(const QString& str) {
  qDebug() << "server!!";
  qDebug() << str;
}

}  // namespace gui