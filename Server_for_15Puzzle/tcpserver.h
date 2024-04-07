#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(int port, QObject *parent = nullptr);
    bool isStarted() const;
    void sendToAll(QString message);
signals:
    void newClientConnected();
    void clientDisconnect();
    void dataReceived(QString message);

private slots:
    void on_client_connecting();

    void clientDisconnected();

    void clientDataReady();


private:
    QTcpServer *_server;
    QList<QTcpSocket *> _socketsList;
    QMap<QString, QVector<int>> m_data;
    bool _isStarted;
};
#endif // TCPSERVER_H
