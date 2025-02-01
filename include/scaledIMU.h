#ifndef SCALEDIMU_H
#define SCALEDIMU_H
#include "pros/imu.hpp"

class scaledIMU : public pros::IMU {

public:
  /**
   * @brief Construct a new scaledIMU object.
   * 
   * @param port The port number where the IMU is connected.
   */
  scaledIMU(int port);

  /**
   * @brief Get the current rotation value from the IMU.
   * 
   * @return The rotation value.
   */
  double get_rotation();

  /**
   * @brief Scaling factor for the IMU readings.
   */
  double IMUscaling;

  /**
   * @brief Offset value for the IMU readings.
   */
  double IMUoffset;
};
#endif // SCALEDIMU_H