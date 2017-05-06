/**
  ******************************************************************************
  * @file    inc/mpu9250.h
  * @author  Adrian Kurylak
  * @version V1.0.0
  * @date    19-April-2017
  * @brief   MPU9250 9-axis sensor communication
  */

#ifndef MPU9250_H_
#define MPU9250_H_
#include "stm32746g_discovery.h"
#include "stm32f7xx.h"
#define SELF_TEST_X_GYRO 0
#define SELF_TEST_Y_GYRO 1
#define SELF_TEST_Z_GYRO 2
#define SELF_TEST_X_ACCEL 13
#define SELF_TEST_Y_ACCEL 14
#define SELF_TEST_Z_ACCEL 15

//#define X_OFFS_USR
//#define Y_OFFS_USR
//#define Z_OFFS_USR

#define ACCEL_XOUT_H 59
#define ACCEL_XOUT_L 60
#define ACCEL_YOUT_H 61
#define ACCEL_YOUT_L 62
#define ACCEL_ZOUT_H 63
#define ACCEL_ZOUT_L 64

#define TEMP_H 65
#define TEMP_L 66

#define GYRO_XOUT_H 67
#define GYRO_XOUT_L 68
#define GYRO_YOUT_H 69
#define GYRO_YOUT_L 70
#define GYRO_ZOUT_H 71
#define GYRO_ZOUT_L 72

#define PWR_MGMT_1 107
#define PWR_MGMT_2 108

uint16_t mpu_get_accel_x();
uint16_t mpu_get_accel_y();
uint16_t mpu_get_accel_z();

#endif /* MPU9250_H_ */
