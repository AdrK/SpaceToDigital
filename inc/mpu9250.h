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

typedef enum __Register
{
	SELF_TEST_X_GYRO = 0,
	SELF_TEST_Y_GYRO = 1,
	SELF_TEST_Z_GYRO = 2
} Register;

void mpu_write_register(Register Reg, uint8_t value);
uint8_t mpu_read_register(Register Reg);

#endif /* MPU9250_H_ */
