#ifndef _EDWART_SUBSYSTEMS_
#define _EDWART_SUBSYSTEMS_

#include "lemlib/chassis/chassis.hpp"
#include "lift.hpp"
#include "pros/adi.hpp"
#include "pros/motors.hpp"

extern lemlib::Chassis chassis;

extern pros::Motor intake;
extern pros::Motor hook;
extern Lift lift;

extern pros::adi::DigitalOut mogo;
extern int mogo_state;

#endif // _EDWART_SUBSYSTEMS_