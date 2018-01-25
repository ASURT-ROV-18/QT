#include "connection.h"

connection::connection() {
  _pSocket = new QTcpSocket();
  _timer = new QTimer();
  this->_delimeter = ";";
  this->_reconnect = false;
  this->_timeout = 500;
  this->_queued = false;
  this->_polling = false;
  this->_networkConnected = false;
  connect(_pSocket, SIGNAL(connected()), this, SLOT(detectConnected()));
  connect(_pSocket, SIGNAL(disconnected()), this, SLOT(detectDisconnected()));
  connect(_pSocket, SIGNAL(error(QAbstractSocket::SocketError)), this,
          SLOT(errorDetected(QAbstractSocket::SocketError)));
  connect(_pSocket, SIGNAL(readyRead()), this, SLOT(readData()));
  connect(_timer, SIGNAL(timeout()), this, SLOT(checkNetwork()));
}

void connection::initializeConnection(
    QHostAddress h /*= QHostAddress::LocalHost*/, int p /*= 8080*/,
    bool rec /*= false*/, int time /*= 500*/) {
  this->_host = h;
  this->_port = p;
  this->_reconnect = rec;
  this->_timeout = time;
  this->_initializeTCP();
}

void connection::_initializeTCP() {
  if (!this->isConnected()) {
    _pSocket->connectToHost(this->_host, this->_port);
    _pSocket->waitForConnected(this->_timeout);
    if (!this->isConnected() && !this->_polling && this->_reconnect) {
      qDebug() << "Couldn't connect. Retrying...";
      _timer->start(this->_timeout);
      this->_polling = true;
    }

    int enableKeepAlive = 1;
    int fd = _pSocket->socketDescriptor();
    setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &enableKeepAlive,
               sizeof(enableKeepAlive));

    int maxIdle = 1; /* seconds */
    setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &maxIdle, sizeof(maxIdle));

    int count =
        2; // send up to 3 keepalive packets out, then disconnect if no response
    setsockopt(fd, IPPROTO_TCP, TCP_KEEPCNT, &count, sizeof(count));

    int interval = 1; // send a keepalive packet out every 2 seconds (after the
                      // 5 second idle period)
    setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(interval));
  }
}

void connection::detectConnected() {
  if (this->_polling) {
    _timer->stop();
    this->_polling = false;
  }
  if (this->_queued) {
    this->write(_queuedMap);
  }
  if (!this->_networkConnected) {
    emit this->networkState(true);
    this->_networkConnected = true;
  }
  emit this->TCPState(true);
}

void connection::detectDisconnected() { emit this->TCPState(false); }

void connection::errorDetected(QAbstractSocket::SocketError err) {
  qDebug() << _pSocket->errorString();
  if ((err == QAbstractSocket::HostNotFoundError ||
       err == QAbstractSocket::SocketTimeoutError ||
       err == QAbstractSocket::NetworkError) &&
      this->_networkConnected) {
    emit this->networkState(false);
    this->_networkConnected = false;
  } else if (err == QAbstractSocket::ConnectionRefusedError &&
             !this->_networkConnected) {
    emit this->networkState(true);
    this->_networkConnected = true;
  }
  if (!this->_polling && this->_reconnect) {
    qDebug() << "starting reconnection";
    _timer->start(this->_timeout);
    this->_polling = true;
  }
}

void connection::checkNetwork() { this->_initializeTCP(); }

bool connection::isConnected() {
  if (_pSocket->state() == QTcpSocket::ConnectedState) {
    return true;
  }
  return false;
}

void connection::write(std::unordered_map<std::string, float> map) {
  auto it = map.begin();
  if (this->isConnected()) {
    if (this->_queued) {
      _queuedMap.clear();
      this->_queued = false;
    }
    std::stringstream sent_string;
    sent_string << "";
    for (; it != map.end(); ++it) {
      sent_string << it->first << " " << std::fixed << std::setprecision(2)
                  << it->second << _delimeter;
    }
    this->_sendTCP(sent_string.str());
  } else {
    this->_queued = true;
    for (; it != map.end(); ++it) {
      _queuedMap[it->first] = it->second;
    }
  }
}

void connection::_sendTCP(std::string m) {
  QByteArray sent_bytes;
  QString msg = QString::fromStdString(m);
  sent_bytes.insert(0, msg);
  _pSocket->write(sent_bytes);
  _pSocket->waitForBytesWritten();
}

void connection::readData() {
  QByteArray data = _pSocket->readAll();
  QString data_qs(data);
  qDebug() << data_qs;
  std::string data_string = data_qs.toUtf8().constData();
  int start = 0, end, space_pos;
  std::unordered_map<std::string, float> received_map;
  while ((end = data_string.find(';', start)) != std::string::npos) {
    space_pos = data_string.find(' ', start);
    received_map[data_string.substr(start, space_pos - start)] =
        stof(data_string.substr(space_pos + 1, end - space_pos - 1));
    start = end + 1;
  }
  emit received(received_map);
}

connection::~connection() {
  delete _pSocket;
  delete _timer;
}
