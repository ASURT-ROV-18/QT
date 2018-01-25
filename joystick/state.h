#pragma once
#include "common.h"
#include <vector>

namespace JS {

class State {
public:
  State(unsigned int button_count, unsigned int axis_count) {
    _buttonCount = button_count;
    _axisCount = axis_count;
    _button = std::vector<JS::Button>(getButtonCount(), 0);
    _axis = std::vector<JS::Axis>(getAxisCount(), 0);

    for (unsigned int i = 0; i < getButtonCount(); ++i) {
      setButton(i, JS::Button(i), StringButtons[i]);
    }

    for (unsigned int i = 0; i < getAxisCount(); ++i) {
      setAxis(i, JS::Axis(i), StringAxes[i]);
    }
  }

  JS::Button &getButton(ButtonID id) {
    return _button[static_cast<unsigned>(id)];
  }
  JS::Button &getButton(unsigned id) { return _button[id]; }


  void setButton(ButtonID id, JS::Button button, std::string title) {
      button.setTitle(title);
    _button[static_cast<unsigned>(id)] = button;
  }


  void setButton(unsigned id, JS::Button button, std::string title) {
      button.setTitle(title);
      _button[id] = button;
  }
  JS::Axis &getAxis(AxisID id) { return _axis[static_cast<unsigned>(id)]; }
  JS::Axis &getAxis(unsigned id) { return _axis[id]; }



  void setAxis(AxisID id, JS::Axis axis, std::string title) {
      axis.setTitle(title);
    _axis[static_cast<unsigned>(id)] = axis;
  }

  void setAxis(unsigned id, JS::Axis axis, std::string title) {
      axis.setTitle(title);
      _axis[id] = axis;
  }

  unsigned int getButtonCount() const { return _buttonCount; }
  unsigned int getAxisCount() const { return _axisCount; }
  ~State() {
        //for (auto &it : _axis)
          //delete it;
        //for (auto &it : _button)
         // delete it;
    _axis.clear();
    _button.clear();
  }

private:
  unsigned int _buttonCount;
  unsigned int _axisCount;
  std::vector<JS::Axis> _axis;
  std::vector<JS::Button> _button;
};
}
