#include "networkhandler.h"

#include <exception>
const QHostAddress NetworkHandler::SERVER_IP(QHostAddress("10.0.1.55"));
//const QHostAddress NetworkHandler::SERVER_IP(QHostAddress::LocalHost);
//const QHostAddress NetworkHandler::SERVER_IP(QHostAddress("192.168.43.8"));
NetworkHandler::NetworkHandler()
{
    QObject(0);
    setTCPConnection(new TCPConnection(TCP_BIND_PORT, TCP_SERVER_PORT, SERVER_IP));
    setUDPConnection(new UDPConnection(UDP_BIND_PORT));

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
    this->udpConnection = udpConnection;
    connect(udpConnection, SIGNAL(dataReceived(QString)),
                        this, SLOT(processDataFromUDP(QString)));
}

void NetworkHandler::setTCPConnection(TCPConnection *tcpConnection)
{
    this->tcpConnection = tcpConnection;
    connect(tcpConnection, SIGNAL(dataReceived(QString)),
                        this, SLOT(processDataFromTCP(QString)));
}

bool NetworkHandler::isUDPSocketValid()
{
    return udpConnection->isReady();
}

NetworkHandler::~NetworkHandler()
{
    delete udpConnection;
    delete tcpConnection;
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

void NetworkHandler::sendTCPMessage(QString message)
{
    try{
        if(tcpConnection->isConnected()){
            qDebug() << message;
            tcpConnection->sendToServer(message);
        }
        else if(tcpConnection->connectToServer()){
            if(tcpConnection->isReady()){
                setTCPConnection(tcpConnection);
                qDebug() <<"reconnected"<<  message;
                tcpConnection->sendToServer(message);
            }
        }
    }
    catch(std::exception e){

    }
}

void NetworkHandler::sendUDPMessage(QString message)
{
    udpConnection->sendTo(message, UDP_PI_PORT, SERVER_IP);
}





