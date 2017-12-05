#include "tcpconnection.h"

TCPConnection::TCPConnection()
{
    QObject(0);
}

TCPConnection::TCPConnection(int port, int serverPort, QHostAddress serverAddress)
{
    QObject(0);
    tcpSocket = new QTcpSocket();
    bindTo(port);
    this->serverAddress = serverAddress;
    this->serverPort = serverPort;
    connectToServer();
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(getReadyData()));
}

bool TCPConnection::bindTo(int port)
{
    if(isReady()){
        tcpSocket->close();
    }
    return tcpSocket->bind(QHostAddress("0.0.0.0"), port);
}

bool TCPConnection::isReady()
{
    return tcpSocket->state() != QAbstractSocket::UnconnectedState
            && tcpSocket->isValid();
}

bool TCPConnection::connectToServer()
{
    tcpSocket->connectToHost(serverAddress, serverPort);
    return tcpSocket->waitForConnected(1000);
}

bool TCPConnection::isConnected()
{
    return tcpSocket->state() == QAbstractSocket::ConnectedState;
}

bool TCPConnection::sendToServer(QString message)
{
    if(isConnected() || connectToServer()){
        tcpSocket->write(message.toUtf8());
        tcpSocket->flush();
        return true;
    }
    return false;
}

bool TCPConnection::changeServer(QHostAddress serverAddress, int serverPort)
{
    this->serverAddress = serverAddress;
    this->serverPort = serverPort;
    return connectToServer();
}


void TCPConnection::getReadyData()
{
    QString receivedMessage = tcpSocket->readAll();
    emit dataReceived(receivedMessage);
}

QTcpSocket* TCPConnection::getTCPSocket()
{
    return tcpSocket;
}

TCPConnection::~TCPConnection()
{
    tcpSocket->close();
}






