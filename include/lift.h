#ifndef LIFT_H
#define LIFT_H

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
  void update();

public:
  Lift(pros::MotorGroup &motors, pros::Rotation &rotation, lemlib::PID pid);
  void goToTop();
  void goToMiddle();
  void goToBottom();
  void goDown();
  void goUp();
};

#endif // LIFT_H