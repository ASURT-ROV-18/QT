#include "networkhandler.h"

NetworkHandler::NetworkHandler()
{
    QObject(0);
}

NetworkHandler::NetworkHandler(UDPConnection *udpConnection)
{
    setUDPConnection(udpConnection);
}

NetworkHandler::NetworkHandler(TCPConnection *tcpConnection)
{
    setTCPConnection(tcpConnection);
}

NetworkHandler::NetworkHandler(UDPConnection *udpConnection, TCPConnection *tcpConnection)
{
    setUDPConnection(udpConnection);
    setTCPConnection(tcpConnection);
}



void NetworkHandler::setUDPConnection(UDPConnection *udpConnection)
{
    if(udpConnection->isReady()){
        this->udpConnection = udpConnection;
        connect(udpConnection, SIGNAL(dataReceived(QString)),
                            this, SLOT(processDataFromUDP(QString)));
    }
}

void NetworkHandler::setTCPConnection(TCPConnection *tcpConnection)
{
    if(tcpConnection->isReady()){
        this->tcpConnection = tcpConnection;
        connect(tcpConnection, SIGNAL(dataReceived(QString)),
                            this, SLOT(processDataFromTCP(QString)));
    }
}

bool NetworkHandler::isUDPSocketValid()
{
    return udpConnection->isReady();
}


/* process the data sent from the PI and emit signals
  for the GUI elements to update */
void NetworkHandler::processDataFromUDP(QString data)
{
    qDebug() << "network Handler :/ data received from UDP /: " << data << endl;
}

void NetworkHandler::processDataFromTCP(QString data)
{
    qDebug() << "network Handler :/ data received from TCP /: " << data << endl;
}



