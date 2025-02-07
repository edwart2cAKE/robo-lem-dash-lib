

#include "lemlib/pid.hpp"
#include "pros/motor_group.hpp"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"
class Lift {
private:
  pros::MotorGroup &m_motors;
  pros::Rotation &m_rotation;
  lemlib::PID m_pid;
  enum State {
    BOTTOM,
    MIDDLE,
    TOP,
  };
  State m_state;
  float getTarget() const {
    // return the target position for the given state
    // TODO: make positions
    switch (m_state) {
    case BOTTOM:
      return 0;
    case MIDDLE:
      return 0;
    case TOP:
      return 0;
    }
    return 0;
  }
  float getRotation() const { return m_rotation.get_position() / 100.0; }
  float getError() const { return getTarget() - getRotation(); }
  void update() {
    const float error = getError();
    const float output = m_pid.update(error);
    m_motors.move_voltage(output);
  }

public:
  Lift(pros::MotorGroup &motors, pros::Rotation &rotation, lemlib::PID pid)
      : m_motors(motors), m_rotation(rotation), m_pid(pid) {
    m_state = BOTTOM;
  }

  void goToTop() { m_state = TOP; }
  void goToMiddle() { m_state = MIDDLE; }
  void goToBottom() { m_state = BOTTOM; }

  void goDown() {
    switch (m_state) {
    case TOP:
      goToMiddle();
      break;
    case MIDDLE:
      goToBottom();
      break;
    case BOTTOM:
      break;
    }
  }
  void goUp() {
    switch (m_state) {
    case TOP:
      break;
    case MIDDLE:
      goToTop();
      break;
    case BOTTOM:
      goToMiddle();
      break;
    }
  }
};