#pragma once
#include "joystick/mode/base.h"
#include "unordered_map"

namespace JS {
namespace Mode {

class General : public Base {
public:
  General(State &state, std::unordered_map &updated_buttons) : _state(state) {
    _id++;
  }
  void enter() {
    _state->getButton(ButtonID::CAM_UP).setType(Button::Type::Hold);
    _state->getButton(ButtonID::CAM_DN).setType(Button::Type::Hold);
    _state->getButton(ButtonID::LightsColors).setType(Button::Type::Toggle);
    _state->getButton(ButtonID::Screenshot).setType(Button::Type::Hold);
    _state->getButton(ButtonID::Z_UP).setType(Button::Type::Toggle);
    _state->getButton(ButtonID::Z_DN).setType(Button::Type::Toggle);
    _state->getButton(ButtonID::LED).setType(Button::Type::Toggle);
  }

  void process() {}
  void exit() {}
  static unsigned getId() { return _id; }

protected:
  State &_state;
  int STEP = 1;
  static unsigned _id;
};
}
}
