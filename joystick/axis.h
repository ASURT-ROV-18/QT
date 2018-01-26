#pragma once
#include <string>

namespace JS {

class Axis {
  enum class Type { Continous, Discrete };

public:
  Axis() = delete;
  Axis(float value) : _id(value), _type(Type::Continous) {}
  Axis(float value, Type type) : _id(value), _type(type) {}
  Axis(float value, Type type, std::string title)
      : _id(value), _type(type), _title(title) {}

  void update(float value) {
    _changed = false;
    _smallChange += value - _value;
    if (_smallChange >= _margin || _smallChange <= -1 * _margin) {
      float v;
      _changed = true;
      _smallChange = 0;
      if (value < _value)
        v = _value - _margin;

      else if (value > _value)
        v = _value + _margin;

      switch (_type) {
      case Type::Continous:
        _value = v;
        _axisValue = value;
        break;
      case Type::Discrete:
        _value = value != 0 ? _value + (value * _step) : 0; // make it continous
        break;
      default:
        break;
      }
    }
  }

  float getValue() const { return _value; }

  unsigned getId() const { return _id; }

  void setType(Type type) { _type = type; }

  void setStep(float step) { _step = step; }

  void setValue(float value) { _value = value; }

  bool wasChanged() const { return _changed; }

  void setTitle(std::string t) { _title = t; }

  std::string getTitle() { return _title; }

  float getAxisValue() { return _axisValue; }

private:
  unsigned _id;
  float _value = 0;
  float _axisValue;
  Type _type;
  float _step = 0.1;
  bool _changed = false;
  float _smallChange = 0;
  float _margin = 5;
  std::string _title;
};
}
