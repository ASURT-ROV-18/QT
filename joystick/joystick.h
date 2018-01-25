#pragma once
#include "backend/base.h"
#include "backend/sfml.h"
#include "button.h"
#include "common.h"
#include "mode/drive.h"
#include "mode/rotation.h"
#include "pipeline.h"
#include "state.h"
#include <QObject>
#include <unordered_map>
#include <vector>

namespace JS {

class Joystick : public QObject {
  Q_OBJECT
public:
  explicit Joystick(unsigned id = 0, BackendID backend_id = BackendID::SFML,
                    QObject *parent = 0);

  unsigned getJoystickIndex() const;

  ~Joystick();

private:
  unsigned _joystick;
  const Backend::Base *_backend;
  Pipeline *_pipeline;
  State *_state, *_old_state;
  bool _connected;
  std::unordered_map<std::string, float> _updated_values;
  float camera_value = 0;
  void init_modes();

public:
  void init();
  bool isConnected() const;

signals:
  void update(std::unordered_map<std::string, float> values);
  void connected(bool connected);

private slots:
  void update_states();
};
}
