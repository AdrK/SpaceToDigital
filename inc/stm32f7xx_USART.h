/**
  ******************************************************************************
  * @file    inc/stm32f7xx_USART.h
  * @author  Adrian Kurylak
  * @version V1.0.0
  * @date    10-April-2017
  * @brief   HAL MSP module header for USART
  */

#include "stm32f7xx_hal_usart.h"

#ifndef STM32F7XX_USART_H_
#define STM32F7XX_USART_H_

#define USARTx									USART6

/* Definitions for UART RCC resources */
#define USART_RCC_CLK_ENABLE					__HAL_RCC_USART6_CLK_ENABLE
#define USART_RCC_CLK_DISABLE					__HAL_RCC_USART6_CLK_DISABLE
#define USART_RCC_FORCE_RESET					__HAL_RCC_USART6_FORCE_RESET
#define USART_RCC_RELEASE_RESET					__HAL_RCC_USART6_RELEASE_RESET

/* Definitions for UART Pins */
#define USART_GPIO_CLK_ENABLE					__HAL_RCC_GPIOC_CLK_ENABLE
#define USART_TX_PIN							GPIO_PIN_6
#define USART_RX_PIN							GPIO_PIN_7
#define USART_TX_PORT							GPIOC
#define USART_RX_PORT							GPIOC

/* Definitions for UART NVIC */
#define USART_IRQn								USART6_IRQn
#define USART_IRQHandler						USART6_IRQHandler

/* Definitions for DMA streams */
#define USART_DMA_CLK_ENABLE					__HAL_RCC_DMA2_CLK_ENABLE
#define USART_DMA_CLK_DISABLE					__HAL_RCC_DMA2_CLK_DISABLE

#define USART_RX_DMA_STREAM						DMA2_Stream2
#define USART_RX_DMA_CHANNEL					DMA_CHANNEL_5
#define USART_DMA_RX_IRQn						DMA2_Stream2_IRQn
#define USART_DMA_RX_IRQHandler					DMA2_Stream2_IRQHandler

#define USART_TX_DMA_STREAM						DMA2_Stream6
#define USART_TX_DMA_CHANNEL					DMA_CHANNEL_5
#define USART_DMA_TX_IRQn						DMA2_Stream6_IRQn
#define USART_DMA_TX_IRQHandler					DMA2_Stream6_IRQHandler

/* Exported handlers */
extern USART_HandleTypeDef g_hUsart;

/* Exported functions */
HAL_StatusTypeDef USART_Init(void);

#endif /* STM32F7XX_USART_H_ */
