// class for scaled IMU sensor
#include "scaledIMU.h"

scaledIMU::scaledIMU(int port, double scaling) : pros::IMU(port) {
  IMUscaling = scaling;
  IMUoffset = 0;
}

double scaledIMU::get_rotation() {
  return (pros::IMU::get_rotation() + IMUoffset) * IMUscaling;
}
