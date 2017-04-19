/**
  ******************************************************************************
  * @file    src/stm32f7xx_it.c
  * @author  Adrian Kurylak
  * @version V1.0.0
  * @date    10-April-2017
  * @brief   Default Interrupt Service Routines.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#ifdef USE_RTOS_SYSTICK
#include <cmsis_os.h>
#endif
#include "stm32f7xx_it.h"
#include "Error_Handler.h"
#include "stm32f7xx_I2C.h"
#include <stm32f7xx_USART.h>
#include "stm32f7xx_SPI.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M7 Processor Exceptions Handlers                         */
/******************************************************************************/

void NMI_Handler(void)
{ Error_Handler(ERROR_NMI); }

void HardFault_Handler(void)
{ Error_Handler(ERROR_HARDFAULT); }

void MemManage_Handler(void)
{ Error_Handler(ERROR_MEMMANAGE); }

void BusFault_Handler(void)
{ Error_Handler(ERROR_BUSFAULT); }

void UsageFault_Handler(void)
{ Error_Handler(ERROR_USAGEFAULT); }

void DebugMon_Handler(void)
{ Error_Handler(ERROR_DEBUGMON); }

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
#ifdef USE_RTOS_SYSTICK
	osSystickHandler();
#endif
}

/******************************************************************************/
/*                 STM32F7xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f7xx.s).                                               */
/******************************************************************************/
void USART_IRQHandler(void)
{
  HAL_USART_IRQHandler(&g_hUsart);
}

void USART_DMA_RX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(g_hUsart.hdmarx);
}

void USART_DMA_TX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(g_hUsart.hdmatx);
}

void I2C_DMA_RX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(g_hI2c.hdmarx);
}

void I2C_DMA_TX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(g_hI2c.hdmatx);
}

void SPIx_IRQHandler(void)
{
  HAL_SPI_IRQHandler(&g_hSpi);
}

void SPIx_DMA_RX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(g_hSpi.hdmarx);
}

void SPIx_DMA_TX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(g_hSpi.hdmatx);
}
