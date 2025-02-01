#include "main.h" // IWYU pragma: keep
#include "subsystems.h"

void pid_single_lateral(int distance) {
  // move the robot to a specific point
  chassis.setPose(0, 0, 0);
  chassis.moveToPoint(distance, 0, 1e9, {.forwards = distance > 0});

  // log the robot's velocity every 10 ms
  // format: (time, velocity)
  while (chassis.isInMotion()) {
    printf("(%d, %f),", pros::millis(), get_chassis_velocity());
    pros::delay(10);
  }
}

void pid_lateral_test() {
  pid_single_lateral(10);
  pid_single_lateral(-20);
  pid_single_lateral(30);
  pid_single_lateral(-40);
  pid_single_lateral(20);
}

void pid_angular_test() {
  chassis.setPose(0, 0, 0);
  chassis.turnToHeading(90, 1000);
}

void pid_suite_test() {
  chassis.setPose(0, 0, 0);
  chassis.moveToPoint(10, 0, 1000);
  chassis.turnToPoint(10, 10, 1000);
  chassis.moveToPoint(10, 10, 1000);
  chassis.turnToPoint(0, 10, 1000);
  chassis.moveToPoint(0, 10, 1000);
  chassis.turnToPoint(0, 0, 1000);
  chassis.moveToPoint(0, 0, 1000);
}

void auto_skills() {}