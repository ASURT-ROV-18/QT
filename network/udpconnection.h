#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H

#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>
#include <exception>

class UDPConnection : public QObject
{
    Q_OBJECT
public:
    UDPConnection();
    UDPConnection(int port);
    bool sendTo(QString message, int port, QHostAddress receiver);
    int getPortNumber();
    bool bindTo(int port);
    bool isReady();
    QUdpSocket *getUDPSocket();
    ~UDPConnection();

signals:
    void dataReceived(QString data);

private:
    QUdpSocket *udpSocket;
    int port;

private slots:
    void getReadyData();
};

#endif // UDPCONNECTION_H
