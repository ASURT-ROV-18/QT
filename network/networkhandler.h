#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H
#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>
#include <exception>
#include "udpconnection.h"
#include "tcpconnection.h"

class NetworkHandler : public QObject
{
     Q_OBJECT
public:
    static const int UDP_PI_PORT = 9010;
    static const int TCP_SERVER_PORT = 9005;
    static const int TCP_BIND_PORT = 9002;
    static const int UDP_BIND_PORT = 9003;
    static const QHostAddress SERVER_IP;

    NetworkHandler();
    NetworkHandler(UDPConnection *udpConnection);
    NetworkHandler(TCPConnection *tcpConnection);
    NetworkHandler(UDPConnection *udpConnection, TCPConnection *tcpConnection);
    void setUDPConnection(UDPConnection *udpConnection);
    void setTCPConnection(TCPConnection *tcpConnection);
    bool isUDPSocketValid();
    ~NetworkHandler();
private:
    UDPConnection *udpConnection;
    TCPConnection *tcpConnection;
public slots:
    void processDataFromUDP(QString data);
    void processDataFromTCP(QString data);
    void sendTCPMessage(QString message);
    void sendUDPMessage(QString message);

signals:
    // signals for the GUI elements to update
};

#endif // NETWORKHANDLER_H
