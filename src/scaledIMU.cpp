// class for scaled IMU sensor
#include "pros/imu.hpp"

class scaledIMU : public pros::IMU {

public:
  scaledIMU(int port);
  double get_rotation();
  double IMUscaling;
  double IMUoffset;
};

scaledIMU::scaledIMU(int port) : pros::IMU(port) {
  IMUscaling = 1;
  IMUoffset = 0;
}

double scaledIMU::get_rotation() {
  return (pros::IMU::get_rotation() + IMUoffset) * IMUscaling;
}
