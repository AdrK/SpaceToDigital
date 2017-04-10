/**
  ******************************************************************************
  * @file    inc/stm32f7xx_I2C.h
  * @author  Adrian Kurylak
  * @version V1.0.0
  * @date    10-April-2017
  * @brief   HAL MSP module header for I2C
  */

#include "stm32f7xx_hal_i2c.h"

#ifndef STM32F7XX_I2C_H_
#define STM32F7XX_I2C_H_

#define I2Cx									I2C1

/* Definitions for I2C RCC resources */
#define I2C_RCC_CLK_ENABLE						__HAL_RCC_I2C1_CLK_ENABLE
#define I2C_RCC_CLK_DISABLE						__HAL_RCC_I2C1_CLK_DISABLE
#define I2C_RCC_FORCE_RESET						__HAL_RCC_I2C1_FORCE_RESET
#define I2C_RCC_RELEASE_RESET					__HAL_RCC_I2C1_RELEASE_RESET

/* Definitions for I2C Pins */
#define I2C_GPIO_CLK_ENABLE						__HAL_RCC_GPIOB_CLK_ENABLE
#define I2C_SCL_PIN								GPIO_PIN_8
#define I2C_SDA_PIN								GPIO_PIN_9
#define I2C_SCL_PORT							GPIOB
#define I2C_SDA_PORT							GPIOB

/* Definitions for DMA streams */
#define I2C_DMA_CLK_ENABLE						__HAL_RCC_DMA1_CLK_ENABLE
#define I2C_DMA_CLK_DISABLE						__HAL_RCC_DMA1_CLK_DISABLE

#define I2C_DMA_RX_STREAM						DMA1_Stream0
#define I2C_DMA_RX_CHANNEL						DMA_CHANNEL_1
#define I2C_DMA_RX_IRQn							DMA1_Stream0_IRQn
#define I2C_DMA_RX_IRQHandler					DMA1_Stream0_IRQHandler

#define I2C_DMA_TX_STREAM						DMA1_Stream6
#define I2C_DMA_TX_CHANNEL						DMA_CHANNEL_1
#define I2C_DMA_TX_IRQn							DMA1_Stream6_IRQn
#define I2C_DMA_TX_IRQHandler					DMA1_Stream6_IRQHandler

/* Exported functions */
HAL_StatusTypeDef I2C_Init(void);

#endif /* STM32F7XX_I2C_H_ */
