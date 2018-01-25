#pragma once
#include "base.h"

namespace JS {
namespace Mode {

class Drive : public Base {

public:
  Drive(State &state) : Base(state) {}
  //  void enter() {}

  void process() {
    auto x = _state.getAxis(AxisID::X);
    auto y = _state.getAxis(AxisID::Y);
    auto povx = _state.getAxis(AxisID::PovX);
    auto povy = _state.getAxis(AxisID::PovY);

    if (x.wasChanged() && x.getValue() < 10 && x.getValue() > -10)
      x.update(0);

    if (y.wasChanged() && y.getValue() < 10 && y.getValue() > -10)
      y.update(0);

    if (povx.wasChanged() && povx.getValue() > 65 && povx.getValue() < -65)
      povx.update(1);
    else
      povx.update(0);

    if (povy.wasChanged() && povy.getValue() > 65 && povy.getValue() < -65)
      povy.update(1);
    else
      povy.update(0);
  }

  //  void exit() {}
};
}
}
