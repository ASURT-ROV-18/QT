#include "udpconnection.h"
#include <QDebug>


UDPConnection::UDPConnection()
{
    QObject(0);
}

UDPConnection::UDPConnection(int port)
{
    QObject(0);
    this->port = port;
    udpSocket = new QUdpSocket();
    bindTo(port);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(getReadyData()));
}

bool UDPConnection::sendTo(QString message, int port, QHostAddress receiver)
{
    if(!isReady())
        return false;
    udpSocket->writeDatagram(message.toUtf8(), receiver, port);
    return true;
}


void UDPConnection::getReadyData()
{
    try{
        QByteArray Buffer;
        Buffer.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(Buffer.data(),Buffer.size());
        QString receivedMessage = Buffer.data();
        emit dataReceived(receivedMessage);
    }
    catch(std::exception e){
        qDebug() << "error receiving message" << endl;
    }
}

int UDPConnection::getPortNumber()
{
    return this->port;
}

bool UDPConnection::bindTo(int port)
{
    if(isReady()){
        udpSocket->close();
    }
    return udpSocket->bind(QHostAddress("0.0.0.0"), port);
}

bool UDPConnection::isReady()
{
    return udpSocket->state() != QAbstractSocket::UnconnectedState
            && udpSocket->isValid();
}

QUdpSocket* UDPConnection::getUDPSocket()
{
    return udpSocket;
}

UDPConnection::~UDPConnection()
{
    udpSocket->close();
}


