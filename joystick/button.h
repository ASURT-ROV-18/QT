#pragma once
#include <string>
namespace JS {

class Button {
public:
  enum class Type { Hold, Toggle };
  Button() = delete;
  Button(unsigned value, Type type = Type::Hold) : _id(value), _type(type) {}
  // Button(unsigned value, Type type = Type::Hold , std::string title) :
  // _id(value), _type(type), _title(title) {}

  void update(bool isPressed) {
    _changed = false;
    switch (_type) {
    case Type::Hold:
      if (_state != isPressed) {
        _state = isPressed;
        _changed = true;
      }
      break;
    case Type::Toggle:
      if (!isPressed && _wasPressed) {
        _state = !_state;
        _changed = true;
      }
      _wasPressed = isPressed;
      break;
    default:
      break;
    }
  }

  bool getState() const { return _state; }

  unsigned getId() const { return _id; }

  Type getType() const { return _type; }

  bool wasChanged() const { return _changed; }

  void setType(Type type) { _type = type; }

  void setState(bool state) { _state = state; }

  std::string getTitle() { return _title; }

  void setTitle(std::string t) { _title = t; }

private:
  unsigned _id;
  bool _state = false;
  bool _wasPressed = false;
  bool _changed = false;
  Type _type;
  std::string _title;
};
}
