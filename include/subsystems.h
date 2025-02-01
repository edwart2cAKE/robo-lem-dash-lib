#ifndef _EDWART_SUBSYSTEMS_
#define _EDWART_SUBSYSTEMS_

#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/motors.hpp"

extern lemlib::Chassis chassis;
double get_chassis_velocity();

extern pros::Motor intake;
extern pros::Motor hook;

extern pros::adi::DigitalOut mogo;
extern int mogo_state;

#endif // _EDWART_SUBSYSTEMS_