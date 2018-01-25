#pragma once
#include "joystick/backend/base.h"
#include <SFML/Window.hpp>

namespace JS {
namespace Backend {

class SFML : public Base {

public:
  const static SFML &init() {
    static SFML instance;
    instance.refresh();
    return instance;
  }

  float getAxisValue(unsigned joystick, unsigned axis) const {
    return sf::Joystick::getAxisPosition(joystick, (sf::Joystick::Axis)axis);
  }
  unsigned getAxisCount(unsigned joystick) const {
    return sf::Joystick::AxisCount;
  }

  unsigned getButtonCount(unsigned joystick) const {
    return sf::Joystick::getButtonCount(joystick);
  }

  bool isButtonPressed(unsigned joystick, unsigned button) const {
    return sf::Joystick::isButtonPressed(joystick, button);
  }

  bool isJoystickConnected(unsigned joystick) const {
    return sf::Joystick::isConnected(joystick);
  }

  SFML(SFML const &) = delete;
  SFML(SFML &&) = delete;
  SFML &operator=(SFML const &) = delete;
  SFML &operator=(SFML &&) = delete;

protected:
  SFML() {}
  ~SFML() {}

private:
  void refresh() { sf::Joystick::update(); }

  void _timerTimeout() {
    refresh();
    emit tick();
  }
};
}
}
