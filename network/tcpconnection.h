#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include <exception>

class TCPConnection : public QObject
{
     Q_OBJECT
public:
    TCPConnection();
    TCPConnection(int port, int serverPort, QHostAddress serverAddress);
    bool bindTo(int port);
    bool isReady();
    bool connectToServer();
    bool isConnected();
    bool sendToServer(QString message);
    bool changeServer(QHostAddress serverAddress, int serverPort);
    QTcpSocket *getTCPSocket();
    ~TCPConnection();

signals:
    void dataReceived(QString data);

private:
    QTcpSocket *tcpSocket;
    int port;
    int serverPort;
    QHostAddress serverAddress;

private slots:
    void getReadyData();

};

#endif // TCPCONNECTION_H
