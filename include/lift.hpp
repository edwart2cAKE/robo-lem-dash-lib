#ifndef LIFT_HPP
#define LIFT_HPP

#include "lemlib/pid.hpp"
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
  float getTarget() const;
  float getRotation() const;
  float getError() const;

public:
  Lift(pros::MotorGroup& motors, pros::Rotation& rotation, lemlib::PID pid);
  void goToTop();
  void goToMiddle();
  void goToBottom();
  void goDown();
  void goUp();
  void update();
};

#endif // LIFT_HPP