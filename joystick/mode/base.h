#pragma once
#include "joystick/common.h"
#include "joystick/state.h"

namespace JS {
namespace Mode {

class Base {
public:
  Base(State &state) : _state(state) { _id++; }
  virtual void enter() = 0;
  virtual void process() = 0;
  virtual void exit() = 0;
  static unsigned getId() { return _id; }

protected:
  State &_state;
  static unsigned _id;
};
}
}
