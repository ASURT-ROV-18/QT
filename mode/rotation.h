#pragma once
#include "base.h"

namespace JS {
namespace Mode {

class Rotation : public Base {

public:
  Rotation(State &state) : Base(state) {}
  //  void enter() {
  //    //_state.getAxis(AxisID::X).update(0);
  //    //_state.getAxis(AxisID::Y).update(0);
  //  }
  void process() {
    _state.getAxis(AxisID::X).update(0);
    _state.getAxis(AxisID::Y).update(0);

    auto povx = _state.getAxis(AxisID::PovX);
    auto povy = _state.getAxis(AxisID::PovY);

    if (povx.wasChanged() && povx.getValue() > 65 && povx.getValue() < -65)
      povx.update(1);
    else
      povx.update(0);

    if (povy.wasChanged() && povy.getValue() > 65 && povy.getValue() < -65)
      povy.update(1);
    else
      povy.update(0);
  }
  //  void exit() { //_state.getAxis(AxisID::U).update(0);
  //  }
};
}
}
