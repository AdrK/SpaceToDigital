/**
  ******************************************************************************
  * @file    inc/stm32f7xx_UART.h
  * @author  Adrian Kurylak
  * @version V1.0.0
  * @date    10-April-2017
  * @brief   HAL MSP module header for UART
  */

#include "stm32f7xx_hal_uart.h"

#ifndef STM32F7XX_UART_H_
#define STM32F7XX_UART_H_

#define UARTx									UART7

/* Definitions for UART RCC resources */
#define UART_RCC_CLK_ENABLE						__HAL_RCC_UART7_CLK_ENABLE
#define UART_RCC_CLK_DISABLE					__HAL_RCC_UART7_CLK_DISABLE
#define UART_RCC_FORCE_RESET					__HAL_RCC_UART7_FORCE_RESET
#define UART_RCC_RELEASE_RESET					__HAL_RCC_UART7_RELEASE_RESET

/* Definitions for UART Pins */
#define UART_GPIO_CLK_ENABLE					__HAL_RCC_GPIOF_CLK_ENABLE
#define UART_TX_PIN								GPIO_PIN_7
#define UART_RX_PIN								GPIO_PIN_6
#define UART_TX_PORT							GPIOF
#define UART_RX_PORT							GPIOF

/* Definitions for UART NVIC */
#define UART_IRQn								UART7_IRQn
#define UART_IRQHandler							UART7_IRQHandler

/* Definitions for DMA streams */
#define UART_DMA_CLK_ENABLE						__HAL_RCC_DMA1_CLK_ENABLE
#define UART_DMA_CLK_DISABLE					__HAL_RCC_DMA1_CLK_DISABLE

#define UART_RX_DMA_STREAM						DMA1_Stream3
#define UART_RX_DMA_CHANNEL						DMA_CHANNEL_5
#define UART_DMA_RX_IRQn						DMA1_Stream3_IRQn
#define UART_DMA_RX_IRQHandler					DMA1_Stream3_IRQHandler

#define UART_TX_DMA_STREAM						DMA1_Stream1
#define UART_TX_DMA_CHANNEL						DMA_CHANNEL_5
#define UART_DMA_TX_IRQn						DMA1_Stream1_IRQn
#define UART_DMA_TX_IRQHandler					DMA1_Stream1_IRQHandler

/* Exported members */
extern UART_HandleTypeDef g_hUart;

/* Exported functions */
HAL_StatusTypeDef UART_Init(void);

#endif /* STM32F7XX_UART_H_ */
