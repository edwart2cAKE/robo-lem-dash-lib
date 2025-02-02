// ports and subsystems are defined here
#include "lemlib/chassis/trackingWheel.hpp"
#include "main.h" // IWYU pragma: keep
#include "scaledIMU.h"

// port numbers
#define left_drive_ports                                                       \
  { -5, -6, -20 }
#define right_drive_ports                                                      \
  { 2, 3, 4 }
#define intake_port -1
#define mogo_port 3
#define imu_port 7

pros::MotorGroup left_side(left_drive_ports);   // left motors on ports 1, 2, 3
pros::MotorGroup right_side(right_drive_ports); // right motors on ports 4, 5, 6

// get the chassis velocity
double get_chassis_velocity() {
  return (left_side.get_actual_velocity() + right_side.get_actual_velocity()) /
         2;
}

// drivetrain settings
lemlib::Drivetrain drivetrain(&left_side,                 // left motor group
                              &right_side,                // right motor group
                              11.25,                      // 10 inch track width
                              lemlib::Omniwheel::OLD_325, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2    // horizontal drift is 2 (for now)
);

scaledIMU imu(imu_port, 360.0 / 180); // inertial sensor

lemlib::OdomSensors sensors(
    nullptr, // vertical tracking wheel 1, set to null
    nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
    nullptr, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a
             // second one
    &imu     // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings
    lateral_controller(15,  // proportional gain (kP)
                       0,   // integral gain (kI)
                       20,  // derivative gain (kD)
                       3,   // anti windup
                       0.5, // small error range, in inches
                       100, // small error range timeout, in milliseconds
                       3,   // large error range, in inches
                       500, // large error range timeout, in milliseconds
                       0    // maximum acceleration (slew)
    );
// angular PID controller
lemlib::ControllerSettings
    angular_controller(2, // proportional gain (kP)
                       0.01,   // integral gain (kI)
                       12,  // derivative gain (kD)
                       3,   // anti windup
                       5,   // small error range, in degrees
                       100, // small error range timeout, in milliseconds
                       3,   // large error range, in degrees
                       500, // large error range timeout, in milliseconds
                       20   // maximum acceleration (slew)
    );

// create drive curve settings
lemlib::ExpoDriveCurve drive_curve(3, 10, 1);

// create turn curve settings
lemlib::ExpoDriveCurve turn_curve(3, 10, 1);

// create the chassis
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller,
                        sensors, &drive_curve, &turn_curve);

// intake
pros::Motor intake(intake_port,pros::v5::MotorGears::green,pros::v5::MotorEncoderUnits::degrees); // intake motor

// mogo
pros::adi::DigitalOut mogo(mogo_port, LOW);
int mogo_state = LOW;
