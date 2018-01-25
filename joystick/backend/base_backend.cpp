#include "joystick/backend/base.h"
#include <QDebug>
using namespace JS::Backend;

Base::Base(QObject *parent) : QObject(parent), _timer(new QTimer(this)) {
  connect(_timer, SIGNAL(timeout()), this, SLOT(_timerTimeout()));
  _timer->start(INTERVAL);
}

// void Base::_timerTimeout() {
//  emit tick();
//}

Base::~Base() {
  _timer->stop();
  delete _timer;
}
