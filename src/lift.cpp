#include "lift.hpp"

// Private helper functions
float Lift::getTarget() const {
  switch (m_state) {
    case BOTTOM: return 5;
    case MIDDLE: return 40;
    case TOP:    return 148;
  }
  return 0;
}

float Lift::getRotation() const { 
  return m_rotation.get_position() / 100.0; 
}

float Lift::getError() const { 
  float error = getTarget() - getRotation();
  printf("Error: %f", error);
  return error;
}

// Constructor
Lift::Lift(pros::MotorGroup& motors, pros::Rotation& rotation, lemlib::PID pid)
  : m_motors(motors), m_rotation(rotation), m_pid(pid)
{
  m_state = BOTTOM;
}

// Public member functions
void Lift::goToTop() { m_state = TOP; }
void Lift::goToMiddle() { m_state = MIDDLE; }
void Lift::goToBottom() { m_state = BOTTOM; }

void Lift::goDown() {
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

void Lift::goUp() {
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

void Lift::update() {
  const float error = getError();
  const float output = m_pid.update(error);
  m_motors.move_voltage(output);
}
