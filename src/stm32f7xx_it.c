/**
  ******************************************************************************
  * @file    stm32f7xx_it.c
  * @author  Ac6
  * @version V1.0
  * @date    02-Feb-2015
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
#include "stm32f7xx_UART.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern UART_HandleTypeDef g_hUart;

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
void UART_IRQHandler(void)
{
  HAL_UART_IRQHandler(&g_hUart);
}

void UART_DMA_RX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(g_hUart.hdmarx);
}

void UART_DMA_TX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(g_hUart.hdmatx);
}
