// ports and subsystems are defined here
#include "lemlib/chassis/trackingWheel.hpp"
#include "lemlib/pid.hpp"
#include "main.h" // IWYU pragma: keep
#include "pros/motor_group.hpp"

#if 0
#include "lift.cpp"
#include "scaledIMU.cpp"
#else
#include "lift.hpp"
#include "scaledIMU.h"
#endif

// port numbers

// drivetrain ports
#define left_drive_ports                                                       \
  { -5, -6, -16 }
#define right_drive_ports                                                      \
  { 13, 14, 15 }

// intkae ports
#define intake_port -12

// lift + rot sensor ports
#define lift_ports                                                             \
  { 20, -19 }
#define rot_sensor_port 10

// mogo port (port C)
#define mogo_port 3

// imu port
#define imu_port 7

pros::MotorGroup left_side(left_drive_ports);   // left motors on ports 1, 2, 3
pros::MotorGroup right_side(right_drive_ports); // right motors on ports 4, 5, 6

// drivetrain settings
lemlib::Drivetrain drivetrain(&left_side,  // left motor group
                              &right_side, // right motor group
                              11.25,       // 11.25 inch track width
                              lemlib::Omniwheel::OLD_325, // using 3.25 omnis
                              450, // drivetrain rpm is 450
                              2    // horizontal drift is 2 (for now)
);

scaledIMU imu(imu_port, 360/357.0); // inertial sensor

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
    angular_controller(2,    // proportional gain (kP)
                       0.01, // integral gain (kI)
                       12,   // derivative gain (kD)
                       3,    // anti windup
                       5,    // small error range, in degrees
                       100,  // small error range timeout, in milliseconds
                       3,    // large error range, in degrees
                       500,  // large error range timeout, in milliseconds
                       20    // maximum acceleration (slew)
    );

// create drive curve settings
lemlib::ExpoDriveCurve drive_curve(3, 10, 1);

// create turn curve settings
lemlib::ExpoDriveCurve turn_curve(3, 10, 1);

// create the chassis
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller,
                        sensors, &drive_curve, &turn_curve);

// intake
pros::Motor intake(intake_port, pros::v5::MotorGears::green,
                   pros::v5::MotorEncoderUnits::degrees); // intake motor

// lady brown
lemlib::PID liftPID(5, 0, 0);

pros::MotorGroup lift_motors(lift_ports, pros::v5::MotorGears::ratio_18_to_1,
                             pros::v5::MotorUnits::invalid); // lift motor group
pros::Rotation lift_sensor(rot_sensor_port);
Lift lift(lift_motors, lift_sensor, liftPID);
pros::Task lift_task([]() {
  lift.update();
  pros::delay(20);
});

// mogo
pros::adi::DigitalOut mogo(mogo_port, LOW);
int mogo_state = LOW;
