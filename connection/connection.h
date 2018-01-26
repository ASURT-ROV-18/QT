#pragma once

#include <QHostAddress>
#include <QMainWindow>
#include <QMap>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QTextCodec>
#include <QTimer>
#include <iomanip>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <unordered_map>

class connection : public QObject {
  Q_OBJECT
private:
  // variables
  QTcpSocket *_pSocket;
  QUdpSocket *_udpSocket;
  QHostAddress _host;
  int _port;
  std::string _delimeter;
  bool _reconnect;
  bool _polling;
  bool _queued;
  bool _networkConnected;
  int _timeout;
  std::unordered_map<std::string, float> _queuedMap;
  QTimer *_timer;

  // functions
  void _initializeTCP();
  void _initializeNetworkSession();
  void _sendTCP(std::string string);

private slots:
  void detectConnected();
  void detectDisconnected();
  void readData();
  void write(std::unordered_map<std::string, float> map);
  void errorDetected(QAbstractSocket::SocketError err);
  void checkNetwork();
signals:
  void TCPState(bool state);
  void networkState(bool state);
  void received(std::unordered_map<std::string, float> map);

public:
  connection();
  void initializeConnection(QHostAddress h = QHostAddress::LocalHost,
                            int p = 8080, bool rec = false, int timeout = 500);
  bool isConnected();
  ~connection();
};
