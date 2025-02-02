#pragma once

#include "lemlib/chassis/chassis.hpp"

extern lemlib::Chassis chassis;

/**
 * Test the lateral PID controller by moving the robot to a specific point.
 *
 * @param distance The distance to move the robot.
 */
void pid_single_lateral(int distance);

/**
 * Test the lateral PID controller by moving the robot to a specific point.
 */
void pid_single_lateral_test();

/**
 * Test the lateral PID controller by moving the robot to various points.
 */
void pid_lateral_test();

/**
 * Test the angular PID controller by turning the robot to a specific heading.
 */
void pid_angular_test();

/**
 * Test both lateral and angular PID controllers by moving and turning the robot
 * to various points.
 */
void pid_suite_test();

/**
 * Execute the autonomous skills routine.
 */
void auto_skills();

void auto_skills_driver();