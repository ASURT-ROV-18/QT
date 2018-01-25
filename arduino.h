#pragma once

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Arduino : public QObject {
  Q_OBJECT
public:
  explicit Arduino(QObject *parent = 0) : QObject(parent) {
    _serial = new QSerialPort();
    for (auto &info : QSerialPortInfo::availablePorts()) {
      if (info.hasVendorIdentifier() && info.hasProductIdentifier() &&
          info.vendorIdentifier() == ARDUINO_UNO_VENDOR_ID &&
          info.productIdentifier() == ARDUINO_UNI_PRODUCT_ID) {

        _serial->setPortName(info.portName());
        _serial->setBaudRate(QSerialPort::Baud9600);
        _serial->setDataBits(QSerialPort::Data8);
        _serial->setParity(QSerialPort::NoParity);
        _serial->setStopBits(QSerialPort::OneStop);
        _serial->setFlowControl(QSerialPort::NoFlowControl);
        break;
      }
    }
  }

  bool Open() { return _serial->open(QSerialPort::WriteOnly); }
  void Close() {
    if (_serial->isOpen())
      _serial->close();
  }

  ~Arduino() {
    Close();
    delete _serial;
  }

private:
  QSerialPort *_serial;
  const unsigned short ARDUINO_UNO_VENDOR_ID = 9025;
  const unsigned short ARDUINO_UNI_PRODUCT_ID = 67;

public slots:
  void write(QString cmd) {
    if (_serial->isWritable()) {
      auto data = QByteArray();
      data.append(cmd);
      _serial->write(data);

    } else {
      // LOG ERROR
    }
  }
};
