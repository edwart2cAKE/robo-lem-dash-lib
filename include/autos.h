#pragma once

#include "lemlib/chassis/chassis.hpp"

extern lemlib::Chassis chassis;

/**
 * Test the lateral PID controller by moving the robot to various points.
 */
void pid_lateral_test();

/**
 * Test the angular PID controller by turning the robot to a specific heading.
 */
void pid_angular_test();

/**
 * Test both lateral and angular PID controllers by moving and turning the robot to various points.
 */
void pid_suite_test();

/**
 * Execute the autonomous skills routine.
 */
void auto_skills();