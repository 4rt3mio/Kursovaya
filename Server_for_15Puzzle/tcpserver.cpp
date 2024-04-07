#include "tcpserver.h"

TcpServer::TcpServer(int port, QObject *parent)
    : QObject{parent}
{
    _server = new QTcpServer(this);
    connect(_server, &QTcpServer::newConnection, this, &TcpServer::on_client_connecting);
    _isStarted = _server->listen(QHostAddress::Any, port);
    if(!_isStarted){
        qDebug() << "Server could not start";
    } else{
        qDebug() << "Server started...";
    }
}

void TcpServer::on_client_connecting()
{
    qDebug() << "a client connected to server";
    auto socket = _server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &TcpServer::clientDataReady);
    connect(socket, &QTcpSocket::disconnected, this, &TcpServer::clientDisconnected);
    _socketsList.append(socket);
    socket->write("Welcome to this Server");
    emit newClientConnected();
}

void TcpServer::clientDisconnected()
{
    emit clientDisconnect();
}

void TcpServer::clientDataReady()
{
    auto socket = qobject_cast<QTcpSocket *>(sender());
    auto data = QString(socket->readAll());
    emit dataReceived(data);

    if (data == "send_map_request") {
        QString reply;
        for (auto it = m_data.constBegin(); it != m_data.constEnd(); ++it) {
            reply += it.key() + " - {";
            for (int i = 0; i < it.value().size(); ++i) {
                reply += QString::number(it.value().at(i));
                if (i < it.value().size() - 1)
                    reply += ", ";
            }
            reply += "}\n";
        }
        socket->write(reply.toUtf8());
    } else {
        QStringList parts = data.split(" - ");
        if (parts.size() != 2) {
            qDebug() << "Invalid message format";
            return;
        }

        QString nic = parts[0];
        int value = parts[1].toInt();

        // Добавляем значение в QMap
        m_data[nic].append(value);
    }
}

bool TcpServer::isStarted() const
{
    return _isStarted;
}

void TcpServer::sendToAll(QString message)
{
    foreach (auto socket, _socketsList) {
        socket->write(message.toUtf8());
    }
}
