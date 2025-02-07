// class for scaled IMU sensor
#include "pros/imu.hpp"

class scaledIMU : public pros::IMU {

public:
  double get_rotation() {
    return (pros::IMU::get_rotation() + m_IMUoffset) * m_IMUscaling;
  };
  scaledIMU(int port, double scaling) : pros::IMU(port) {
    m_IMUscaling = scaling;
    m_IMUoffset = 0;
  }

private:
  double m_IMUscaling;
  double m_IMUoffset;
};

