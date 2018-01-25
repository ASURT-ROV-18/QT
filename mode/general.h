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
    _state->getButton(ButtonID::CAM_UP).setType(Button::Type::Toggle);
    _state->getButton(ButtonID::CAM_DN).setType(Button::Type::Toggle);
    _state->getButton(ButtonID::LightsColors).setType(Button::Type::Toggle);
    _state->getButton(ButtonID::Screenshot).setType(Button::Type::Toggle);
    _state->getButton(ButtonID::Z_UP).setType(Button::Type::Toggle);
    _state->getButton(ButtonID::Z_DN).setType(Button::Type::Toggle);
    //_state->getButton(ButtonID::CAM).setType(Button::Type::Toggle);
  }

  void process() {
    // mode updates values and puts in dictionary, joystick sends signal
    // listeners receive signal, listeners examine dictionary
    // tadaaaa
    for (auto const button_id : MyJoystick._pipeline->_button_ids) {
      auto button = _state.getButton(button_id);
      if (!button.wasChanged())
        continue;
      if (_state.getButton(ButtonID::CAM_UP).wasChanged())
        updated_buttons[ButtonID::CAM] += 1;
      else if (_state.getButton(ButtonID::CAM_UP).wasChanged())
        updated_buttons[ButtonID::CAM] -= 1;
      // INCOMPLETE
    }
  }
  void exit() {}
  static unsigned getId() { return _id; }

protected:
  State &_state;
  int STEP = 1;
  static unsigned _id;
};
}
}

/*


   case ButtonID::LightsColors :
       {
       //send char to illuminate LED
       break;
       }

   case ButtonID::Screenshot :
       {
       //take screenshot
       //save screenshot
       //send screenshot to image processing

       break;
       }

   case ButtonID::Z_UP :
       {
       auto zup = _state.getAxis(AxisID::Z);
       zup.update(zup.getValue() + STEP);
       break;
       } //Update Z axis with added STEP

   case ButtonID::Z_DN :
       {
       auto zdown = _state.getAxis(AxisID::Z);
       zdown.update(zdown.getValue() - STEP);
       break;
       } //Updates Z axis with subtracted STEP
   }
 */ // THIS IS THE ORIGINAL IMPLEMENTATION OF PROCESS()
