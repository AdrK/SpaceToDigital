/**
  ******************************************************************************
  * @file    inc/mpu9250.c
  * @author  Adrian Kurylak
  * @version V1.0.0
  * @date    19-April-2017
  * @brief   MPU9250 9-axis sensor communication
  */

#include "mpu9250.h"
#include "stm32f7xx_SPI.h"
#include <stdio.h>
#include <stdlib.h>

static uint8_t mpu_read_byte(uint8_t reg);
static uint8_t mpu_read_register(uint8_t reg);
static void mpu_write_byte(uint8_t data);
static void mpu_write_register(uint8_t reg, uint8_t* value);
static void mpu_request_read(uint8_t addr);
static void mpu_request_write(uint8_t addr);

// TODO: Error handling
// TODO: Implement assertions
// TODO: Values assertions
// TODO: Better register handling
// TODO: Bitfields for registers
// TODO: Set 2C_IF_DIS

static void mpu_request_read(uint8_t addr)
{
	// Reset MSB to indicate read operation
	mpu_write_byte((uint8_t)~0x80 & addr);
}

static void mpu_request_write(uint8_t addr)
{
	// Set MSB to indicate write operation
	mpu_write_byte((uint8_t)0x80 | addr);
}

static uint8_t mpu_read_byte(uint8_t reg)
{
	uint8_t data=0;
	HAL_SPI_Receive_DMA(&g_hSpi, &data, 1);
	return data;
}

static void mpu_write_byte(uint8_t data)
{
	HAL_SPI_Transmit_DMA(&g_hSpi, &data, 1);
}

static uint8_t mpu_read_register(uint8_t reg)
{
	mpu_request_read(reg);
	return mpu_read_byte(reg);
}

static void mpu_write_register(uint8_t reg, uint8_t* value)
{
	mpu_request_write(reg);
	mpu_write_byte(value);
}

uint16_t mpu_get_accel_x()
{
	uint8_t high, low;
	high = mpu_read_register(GYRO_XOUT_H);
	low = mpu_read_register(GYRO_XOUT_L);

	return (uint16_t) (high << 8 | low) ;
}

uint16_t mpu_get_accel_y()
{
	uint8_t high, low;
	high = mpu_read_register(GYRO_YOUT_H);
	low = mpu_read_register(GYRO_YOUT_L);

	return (uint16_t) (high << 8 | low) ;
}

uint16_t mpu_get_accel_z()
{
	uint8_t high, low;
	high = mpu_read_register(GYRO_ZOUT_H);
	low = mpu_read_register(GYRO_ZOUT_L);

	return (uint16_t) (high << 8 | low) ;
}
