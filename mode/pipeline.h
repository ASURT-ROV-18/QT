#pragma once
#include "mode/base.h"
#include <vector>

namespace JS {
class Pipeline {

public:
  Pipeline() {}

  void add(Mode::Base *mode) { _modes.push_back(mode); }

  void link(unsigned int index) { _modes[index]->enter(); }

  void process() {
    for (auto const &mode : _modes) {
      if (mode->isActive())
        mode->process();
    }
  }

  void unlink(unsigned int index) { _modes[index]->exit(); }

private:
  std::vector<Mode::Base *> _modes;
};
}
