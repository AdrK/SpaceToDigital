/**
  ******************************************************************************
  * @file    inc/stm32f7xx_SPI.h
  * @author  Adrian Kurylak
  * @version V1.0.0
  * @date    10-April-2017
  * @brief   HAL MSP module header for SPI
  */

#include "stm32f7xx_hal_spi.h"

#ifndef STM32F7XX_SPI_H_
#define STM32F7XX_SPI_H_


/* Definitions for SPIx RCC resources */
#define SPIx											SPI5
#define SPIx_CLK_ENABLE()								__HAL_RCC_SPI5_CLK_ENABLE()
#define SPIx_DMAx_CLK_ENABLE()							__HAL_RCC_DMA2_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()						__HAL_RCC_GPIOF_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE()						__HAL_RCC_GPIOF_CLK_ENABLE()
#define SPIx_MOSI_GPIO_CLK_ENABLE()						__HAL_RCC_GPIOF_CLK_ENABLE()
#define SPIx_NSS_GPIO_CLK_ENABLE()						__HAL_RCC_GPIOF_CLK_ENABLE()

#define SPIx_FORCE_RESET()								__HAL_RCC_SPI5_FORCE_RESET()
#define SPIx_RELEASE_RESET()							__HAL_RCC_SPI5_RELEASE_RESET()

/* Definitions for SPIx Pins */
#define SPIx_SCK_PIN									GPIO_PIN_7
#define SPIx_SCK_GPIO_PORT								GPIOF
#define SPIx_MISO_PIN									GPIO_PIN_8
#define SPIx_MISO_GPIO_PORT								GPIOF
#define SPIx_MOSI_PIN									GPIO_PIN_9
#define SPIx_MOSI_GPIO_PORT								GPIOF
#define SPIx_NSS_PIN									GPIO_PIN_6
#define SPIx_NSS_PORT									GPIOF

/* Definitions for SPIx's DMA */
#define SPIx_TX_DMA_STREAM								DMA2_Stream4
#define SPIx_RX_DMA_STREAM								DMA2_Stream3
#define SPIx_TX_DMA_CHANNEL								DMA_CHANNEL_2
#define SPIx_RX_DMA_CHANNEL								DMA_CHANNEL_2

/* Definitions for SPIx's NVIC */
#define SPIx_IRQn										SPI5_IRQn
#define SPIx_IRQHandler									SPI5_IRQHandler

#define SPIx_DMA_TX_IRQn								DMA2_Stream4_IRQn
#define SPIx_DMA_RX_IRQn								DMA2_Stream3_IRQn

#define SPIx_DMA_TX_IRQHandler							DMA2_Stream4_IRQHandler
#define SPIx_DMA_RX_IRQHandler							DMA2_Stream3_IRQHandler

/* Exported handlers */
extern SPI_HandleTypeDef g_hSpi;
extern DMA_HandleTypeDef g_hSpiTxDma, g_hSpiRxDma;

/* Exported functions */
HAL_StatusTypeDef SPI_Init(void);

#endif /* STM32F7XX_SPI_H_ */
