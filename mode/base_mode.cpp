#include "joystick/mode/base.h"

unsigned JS::Mode::Base::_id = 0;

void JS::Mode::Base::enter() { _active = true; }

void JS::Mode::Base::exit() { _active = false; }
