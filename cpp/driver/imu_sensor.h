/*
 * Copyright 2016 <Admobilize>
 * All rights reserved.
 */

#ifndef CPP_DRIVER_IMU_SENSOR_H_
#define CPP_DRIVER_IMU_SENSOR_H_

#include <string>
#include "./matrix_driver.h"
#include "./imu_data.h"

namespace matrix_hal {

class IMUSensor : public MatrixDriver {
 public:
  bool Read(IMUData* data);
};
};      // namespace matrix_hal
#endif  // CPP_DRIVER_IMU_SENSOR_H_
