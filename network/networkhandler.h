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
    NetworkHandler();
    NetworkHandler(UDPConnection *udpConnection);
    NetworkHandler(TCPConnection *tcpConnection);
    NetworkHandler(UDPConnection *udpConnection, TCPConnection *tcpConnection);
    void setUDPConnection(UDPConnection *udpConnection);
    void setTCPConnection(TCPConnection *tcpConnection);
    bool isUDPSocketValid();
private:
    UDPConnection *udpConnection;
    TCPConnection *tcpConnection;
private slots:
    void processDataFromUDP(QString data);
    void processDataFromTCP(QString data);
    // todo add slot for the Joystick to send data when ready

signals:
    // signals for the GUI elements to update
};

#endif // NETWORKHANDLER_H
