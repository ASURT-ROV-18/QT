#pragma once
#include "base.h"

namespace JS {
namespace Mode {

class Drive : public Base {

public:
  Drive(State &state) : Base(state) {}
  void enter() {
  _state.getAxis(AxisID::R).update(0);
}
  void process() {
//    if(_state.getAxis(AxisID::X).wasChanged())
      //_state.getAxis(AxisID::X).update(_state.getAxis(AxisID::X).getValue() * -1);

    if (_state.getAxis(AxisID::X).wasChanged() && _state.getAxis(AxisID::X).getAxisValue() < 15 && _state.getAxis(AxisID::X).getAxisValue() > -15)
      _state.getAxis(AxisID::X).update(0);

    if (_state.getAxis(AxisID::Y).wasChanged() && _state.getAxis(AxisID::Y).getAxisValue() < 15 && _state.getAxis(AxisID::Y).getAxisValue() > -15)
      _state.getAxis(AxisID::Y).update(0);

    if (_state.getAxis(AxisID::PovX).getAxisValue() > 0)  _state.getAxis(AxisID::PovX).update(100);
    if (_state.getAxis(AxisID::PovX).getAxisValue() < 0)  _state.getAxis(AxisID::PovX).update(-100);
    if (_state.getAxis(AxisID::PovY).getAxisValue() > 0)  _state.getAxis(AxisID::PovY).update(100);
    if (_state.getAxis(AxisID::PovY).getAxisValue() < 0)  _state.getAxis(AxisID::PovY).update(-100);


    else
      _state.getAxis(AxisID::PovX).update(0);

    if(_state.getAxis(AxisID::PovY).getValue() > 65 && _state.getAxis(AxisID::PovY).getValue() < -65)

      _state.getAxis(AxisID::PovY).update(1);
    else
      _state.getAxis(AxisID::PovY).update(0);
  }

  void exit() {}

private:
  const float STEP = 0.25;
  // Base interface
};
}
}
