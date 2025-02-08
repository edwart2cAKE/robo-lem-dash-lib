#include "main.h" // IWYU pragma: keep
#include "subsystems.h"

// pid single tests lateral
void pid_lateral_test() {
  chassis.moveToPoint(0, 10, 1e4);
  chassis.moveToPoint(0, -10, 1e4, {.forwards = false});
  chassis.moveToPoint(0, 0, 1e4);
}

// pid angular tests
void pid_angular_test() {
  chassis.setPose(0, 0, 0);
  chassis.turnToHeading(90, 10000, {}, false);
  // pros::delay(1000);
  chassis.turnToHeading(135, 10000, {}, false);
  // pros::delay(1000);
  chassis.turnToHeading(157.5, 10000, {}, false);
  chassis.turnToHeading(0, 10000);
}

// pid suite test
void pid_suite_test() {
  int timeout = 10000;
  chassis.setPose(0, 0, 0);
  chassis.turnToHeading(90, timeout);
  chassis.moveToPoint(30, 0, timeout);
  chassis.turnToPoint(30, 30, timeout);
  chassis.moveToPoint(30, 30, timeout);
  chassis.turnToPoint(0, 30, timeout);
  chassis.moveToPoint(0, 30, timeout);
  chassis.turnToPoint(0, 0, timeout);
  chassis.moveToPoint(0, 0, timeout);
  chassis.turnToHeading(0, timeout);
}

// auto skills driver
void auto_skills_driver() {
  // set position
  chassis.setPose(0, -59, 0);
  {
    // score ring in intake
    intake.move(127);
    chassis.tank(-30, -30);
    pros::delay(500);
    intake.move(0);
    chassis.tank(0, 0);
    intake.move(-127);

    // get right mogo
    chassis.moveToPoint(0, -49.375, 1500);
    pros::delay(500);
    intake.move(0);
    chassis.turnToHeading(-90, 1500);
    chassis.moveToPoint(19, -49.375, 3500, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntil(18);
    mogo.set_value(1);
  }
}

// auto skills
void auto_skills() {
  // set position
  auto_skills_driver();
  // get group of 5 rings
  chassis.turnToPoint(20, -20, 1500, {.maxSpeed = 50});
  chassis.waitUntilDone();
  intake.move(127);
  chassis.moveToPoint(20, -24, 2000, {.maxSpeed = 70});

  chassis.turnToHeading(90, 1500, {.maxSpeed = 70});
  chassis.moveToPoint(46, -24, 2500, {.maxSpeed = 50});
  chassis.waitUntilDone();
  pros::delay(1000);

  chassis.turnToHeading(170, 1500, {.maxSpeed = 70});
  chassis.moveToPoint(46, -57, 7000, {.maxSpeed = 30});
  chassis.waitUntilDone();
  pros::delay(1000);

  chassis.moveToPoint(46, -48, 1500, {.forwards = false, .maxSpeed = 50});

  chassis.turnToHeading(90, 1500);
  chassis.moveToPoint(59, chassis.getPose().y, 1500,
                      {.maxSpeed = 60, .minSpeed = 40});
  chassis.waitUntilDone();
  pros::delay(1000);
  chassis.moveToPoint(48, -48, 1200, {.forwards = false, .maxSpeed = 50});

  // score rings in goal
  chassis.turnToHeading(-40, 1200);
  chassis.moveToPoint(53, -57, 2000, {.forwards = false, .maxSpeed = 50});
  chassis.waitUntilDone();
  mogo.set_value(0);
  //*/
  // chassis.setPose(57, -57, -45);
  // move to other side
  // copy of above code but mirrored
  // get left mogo
  // chassis.turnToPoint(-20, -49, 2000, {.forwards = false});
  chassis.moveToPoint(42, -42, 2000);

  chassis.turnToHeading(93, 2000);
  chassis.moveToPoint(0, -42, 4000,
                      {.forwards = false,
                       .maxSpeed = 100,
                       .minSpeed = 50,
                       .earlyExitRange = 10});
  chassis.moveToPoint(-26, -42, 6000, {.forwards = false, .maxSpeed = 50});
  chassis.waitUntil(25);
  mogo.set_value(1);

  // get group of 5 rings
  chassis.turnToPoint(-24, -24, 2000, {.maxSpeed = 70});
  chassis.moveToPoint(-24, -24, 2000, {.maxSpeed = 50, .minSpeed = 30});

  chassis.turnToPoint(-48, -24, 2000);
  chassis.moveToPoint(-48, -24, 2000, {.maxSpeed = 50, .minSpeed = 30});

  chassis.turnToHeading(180, 1500);
  chassis.moveToPoint(-48, -55, 7000, {.maxSpeed = 30, .minSpeed = 20});

  chassis.moveToPoint(-48, -48, 1500, {.forwards = false, .maxSpeed = 50});

  // score mogo in corner
  chassis.turnToHeading(45, 1500);
  chassis.moveToPoint(-60, -60, 1500, {.forwards = false, .maxSpeed = 50});
  chassis.waitUntilDone();
  mogo.set_value(0);

  /*/ go to other side
  chassis.turnToPoint(-48, 0, 1500);
  chassis.moveToPoint(-48, 0, 1500);

  chassis.turnToPoint(0, 60, 1500);
  chassis.moveToPoint(0, 60, 1500);

  // push first mogo
  chassis.turnToPoint(-60, 60, 1500, {.forwards = false});
  chassis.moveToPoint(-60, 60, 1500, {.forwards = false});
  //*/
}

// 
