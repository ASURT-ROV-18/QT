#include "joystick.h"
#include <QDebug>
#include <cmath>
#define Z_OFFSET 100

using namespace JS;

Joystick::Joystick(unsigned id, BackendID backend_id, QObject *parent)
    : QObject(parent), _joystick(id) {
  switch (backend_id) {
  case BackendID::SFML:
    _backend = &Backend::SFML::init();
    break;
  default:
    break;
  }
}

void Joystick::init() {
  _connected = _backend->isJoystickConnected(getJoystickIndex());
  emit connected(_connected);
  connect(_backend, SIGNAL(tick()), this, SLOT(update_states()));
  if (!_connected)
    return;
  init_modes();
}

unsigned Joystick::getJoystickIndex() const { return _joystick; }

Joystick::~Joystick() {
  delete _backend;
  delete _pipeline;
  delete _state;
  delete _old_state;
}

bool Joystick::isConnected() const { return _connected; }

void Joystick::init_modes() {
  _state = new State(_backend->getButtonCount(getJoystickIndex()),
                     _backend->getAxisCount(getJoystickIndex()));
  _old_state = new State(_backend->getButtonCount(getJoystickIndex()),
                         _backend->getAxisCount(getJoystickIndex()));

  // TODO: add General Mode
  _pipeline = new Pipeline(_state);
  _pipeline->add(ButtonID::Drive, new Mode::Drive(*_state));
  _pipeline->add(ButtonID::Rotation, new Mode::Rotation(*_state));

  _pipeline->link(ButtonID::Drive);
  _pipeline->unlink(ButtonID::Rotation);
}

void Joystick::update_states() { // Checks states of buttons and axes
  bool changed = false;
  bool reconnected = false;
  auto isCurrentlyConnected = _backend->isJoystickConnected(getJoystickIndex());

  if (isCurrentlyConnected != _connected)
  {
    qDebug() << "Connected";
    emit connected(isCurrentlyConnected);
    reconnected = true;
  }
  _connected = isCurrentlyConnected;

  if (!isConnected()) {
      qDebug() << "Joystick is not connected";
    // delete state ?
    return;
  }

  // std::unordered_map<std::string, float> _updated_values;
  if(reconnected) init_modes();
  (*_old_state) = (*_state);
  for (unsigned i = 0; i < _state->getAxisCount(); ++i) {
    auto value = _backend->getAxisValue(getJoystickIndex(), i);
    _state->getAxis(i).update(value);
  }
  for (unsigned i = 0; i < _state->getButtonCount(); ++i) {
    auto value = _backend->isButtonPressed(getJoystickIndex(), i);
    _state->getButton(i).update(value);
  }

  _pipeline->process();



  if (_state->getButton(ButtonID::Rotation).getState()) {
    _pipeline->link(ButtonID::Rotation);
    _pipeline->unlink(ButtonID::Drive); }
  else {
    _pipeline->unlink(ButtonID::Rotation);
    _pipeline->link(ButtonID::Drive);

  }
  if (_state->getButton(ButtonID::CAM_UP).getState() ||
      _state->getButton(ButtonID::CAM_DN).getState()) {
    changed = true;
    if (_state->getButton(ButtonID::CAM_UP).getState())
      camera_value = std::min(camera_value + 1.0, 45.0);

    else if (_state->getButton(ButtonID::CAM_DN).getState())
      camera_value = std::max(camera_value - 1.0, -45.0);

    _updated_values["CAM"] = camera_value;
    qDebug() << "CAM " << _updated_values["CAM"];
  }

  for (unsigned i = 0; i < _state->getAxisCount(); i++) {
    if (i == (int)AxisID::Z || _state->getAxis(i).getTitle() == "unused")
      continue;

    if (_state->getAxis(i).getValue() != _old_state->getAxis(i).getValue()) {
      changed = true;
      auto value = _state->getAxis(i).getValue();
      if(i == (int)AxisID::X) value *= -1;
      _updated_values[_state->getAxis(i).getTitle()] = -1 * value;
     // qDebug() << QString::fromStdString(_state->getAxis(i).getTitle()) << "   "
       //        << _updated_values[_state->getAxis(i).getTitle()];
    }
  }
  for (unsigned i = 0; i < _state->getButtonCount(); i++) {
    if (i == (int)ButtonID::CAM_UP || i == (int)ButtonID::CAM_DN ||
        i == (int)ButtonID::CAM)
      continue;

    if ((_state->getButton(i).getState() != _old_state->getButton(i).getState())
          || (_state->getAxis(AxisID::Z).getValue() != _old_state->getAxis(AxisID::Z).getValue())) {
        changed = true;

      if(_state->getAxis(AxisID::Z).getValue() != _old_state->getAxis(AxisID::Z).getValue()
              ||_state->getButton(ButtonID::Z_UP).wasChanged()
                                            || _state->getButton(ButtonID::Z_DN).wasChanged()) {

      if (_state->getButton(ButtonID::Z_UP).getState())
        _updated_values["Z"] = -1 * (_state->getAxis(AxisID::Z).getValue() - Z_OFFSET) / 2;

      else if (_state->getButton(ButtonID::Z_DN).getState())
        _updated_values["Z"] = (_state->getAxis(AxisID::Z).getValue() - Z_OFFSET) / 2;

      else if ((_state->getButton(ButtonID::Z_DN).wasChanged() || _state->getButton(ButtonID::Z_UP).wasChanged())
               && !(_state->getButton(ButtonID::Z_DN).getState() && _state->getButton(ButtonID::Z_UP).getState()))
     {
        _updated_values["Z"] = 0;
      }//qDebug() << "Z" << " = " << _updated_values["Z"];

      }

      else {
          if (i == (int)ButtonID::Z_UP || i == (int)ButtonID::Z_DN || _state->getButton(i).getTitle() == "unused") continue;
        _updated_values[_state->getButton(i).getTitle()] = _state->getButton(i).getState();
      }
    }
  }

  if(reconnected) {
      for(unsigned i = 0 ; i < _state->getAxisCount() ; i++)
      {
          if(_state->getAxis(i).getTitle() == "unused") continue;
          _updated_values[_state->getAxis(i).getTitle()] = 0;
          qDebug() << _updated_values[_state->getAxis(i).getTitle()];
      }
  }

  if (changed) {
      qDebug() << "call";
    emit update(_updated_values);
  }
  _updated_values.clear();
  changed = false;
}
