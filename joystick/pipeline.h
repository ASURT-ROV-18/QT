#pragma once
#include "joystick/common.h"
#include "joystick/mode/base.h"
#include "joystick/state.h"
#include <unordered_map>
#include <vector>

namespace JS {
class Pipeline {

public:
  Pipeline(State *state) : _state(state) {}

  void add(ButtonID button_id, Mode::Base *mode) {
    _store[button_id] = mode;
    _button_ids.push_back(button_id);
  }

  void link(ButtonID button_id) {
    auto mode = _store[button_id];
    _modes.push_back(mode);
    mode->enter();
  }

  void process() {
    for (auto const &button_id : _button_ids) {
      auto button = _state->getButton(button_id);
      if (!button.wasChanged())
        continue;
      if (button.getState())
        link(button_id);
      else
        unlink(button_id);
    }
    for (auto const &mode : _modes) {
      mode->process();
    }
  }

  void unlink(ButtonID button_id) {
    JS::Mode::Base *mode = _store[button_id];
    mode->exit();
    for (unsigned i = 0; i < _modes.size(); ++i) {
      if (mode == _modes[i] && mode->getId() == _modes[i]->getId()) {
        _modes.erase(_modes.begin() + i);
        break;
      }
    }
  }

private:
  State *_state;
  std::unordered_map<ButtonID, Mode::Base *> _store;
  std::vector<ButtonID> _button_ids;
  std::vector<Mode::Base *> _modes;
};
}
