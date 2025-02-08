#include "main.h"
#include "autos.h"
#include "pros/abstract_motor.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "subsystems.h"


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

// add autos
rd::Selector selector({{"PID lateral", &pid_lateral_test},
                       {"PID angular", &pid_angular_test},
                       {"PID total", &pid_suite_test},
                       {"Auto Skills", &auto_skills}});

rd::Console console;

pros::Controller master(pros::E_CONTROLLER_MASTER);

int is_comp{0};

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

  // set up chassis
  chassis.calibrate();

  // set up intake and hook
  intake.set_brake_mode(pros::MotorBrake::brake);


  console.focus();

  // print position to brain screen
  pros::Task update_task([&]() {
    while (true) {
      // clear screen
      console.clear();

      // print robot location to the brain screen
      console.printf("X: %f \n", chassis.getPose().x);           // x
      console.printf("Y: %f \n", chassis.getPose().y);           // y
      console.printf("Heading: %f \n", chassis.getPose().theta); // heading

      // print comp status
      console.printf("Is Competition %f \n", is_comp);

      

      // delay to save resources
      pros::delay(50);
    }
  });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  console.focus();
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  // Run the selected autonomous function
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
  auto_skills();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
bool doing_auto = false;
void opcontrol() {
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
  while (1) {
    // intake control (R1 / R2)
    int intake_movement = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) -
                          master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    intake.move(127 * intake_movement);

    // mogo control (down)
    if (master.get_digital_new_press(DIGITAL_DOWN)) {
      mogo_state = !mogo_state;
      mogo.set_value(mogo_state);
    }

    // lift control (L1 / L2)
    if (master.get_digital_new_press(DIGITAL_L2)) {
      lift.goUp();
    } else if (master.get_digital_new_press(DIGITAL_L1)) {
      lift.goDown();
    } //*/

    // chassis control (tank drive)
    int left = master.get_analog(ANALOG_LEFT_Y);
    int right = master.get_analog(ANALOG_RIGHT_Y);
    chassis.tank(left, right, false);

    // delay
    pros::delay(20);
  }
}