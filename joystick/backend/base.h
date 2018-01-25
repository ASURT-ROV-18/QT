#pragma once
#include <QObject>
#include <QTimer>

namespace JS {
namespace Backend {

class Base : public QObject
{
  Q_OBJECT
public:
  explicit Base(QObject* parent = 0);
  virtual ~Base();
  virtual float getAxisValue(unsigned joystick, unsigned axis) const = 0;
  virtual unsigned getAxisCount(unsigned joystick) const = 0;
  virtual unsigned getButtonCount(unsigned joystick) const = 0;
  virtual bool isButtonPressed(unsigned joystick, unsigned button) const = 0;
  virtual bool isJoystickConnected(unsigned joystick) const = 0;
signals:
  void tick();

private:
  virtual void refresh() = 0;
  const unsigned INTERVAL = 50;
  QTimer* _timer;
private slots:
  virtual void _timerTimeout() = 0;
};
}
}
