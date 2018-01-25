#pragma once
#include "axis.h"
#include "button.h"
#include <string>

namespace JS {

enum class BackendID { SFML, SDL, SDL2, QGameController };

enum class ButtonID {
  Rotation = 0,
  Screenshot = 1,
  Z_DN = 2,
  CAM_DN = 3,
  Z_UP = 4,
  CAM_UP = 5,
  Drive = 6,
  SPD_DN = 10,
  SPD_UP = 11,
  CAM = 13
};

enum class AxisID {
  X = 0,
  Y = 1,
  Z = 2, // Light intensity
  R = 3,
  U = 4,
  PovX = 5,
  PovY = 6,
  UNKNOWN = 7
};
}

const std::string StringButtons[] = {
    "Rotation", "Screenshot", "Z_DN", "CAM_DN", "Z_UP",   "CAM_UP","unused",
    "unused","unused","unused",     "SPD_DN", "SPD_UP","unused",     "CAM",
};
const std::string StringAxes[] = {"X", "Y",       "Speed", "R",
                                  "unused", "unused", "PovX",  "PovY"};
