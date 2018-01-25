#pragma once
#include "joystick/common.h"
#include "joystick/state.h"

namespace JS {
namespace Mode {

class Base {
public:
  Base(State &state) : _state(state) { _id++; }
  virtual void enter();
  virtual void process() = 0;
  virtual void exit();
  static unsigned getId() { return _id; }
  bool isActive() const { return _active; }

protected:
  State &_state;
  static unsigned _id;
  bool _active;
};
}
}
