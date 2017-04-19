/**
  ******************************************************************************
  * @file    src/stm32f7xx_USART.c
  * @author  Adrian Kurylak
  * @version V1.0.0
  * @date    10-April-2017
  * @brief   HAL MSP module for USART
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include <stm32f7xx_USART.h>

/* Private variables ---------------------------------------------------------*/
USART_HandleTypeDef g_hUsart;
uint8_t g_UsartTxBuffer[1024];
uint8_t g_UsartRxBuffer[1024];
DMA_HandleTypeDef g_hUsartTxDma;
DMA_HandleTypeDef g_hUsartRxDma;

/* Private function prototypes -----------------------------------------------*/
HAL_StatusTypeDef USART_Init(void);
void HAL_USART_MspInit(USART_HandleTypeDef *hUsart);
void HAL_USART_MspDeInit(USART_HandleTypeDef *hUsart);

/* Private functions ---------------------------------------------------------*/

HAL_StatusTypeDef USART_Init(void)
{
	HAL_StatusTypeDef ERR_CODE;

	g_hUsart.Instance = USARTx;
	g_hUsart.Init.BaudRate = 9600;
	g_hUsart.Init.Mode = USART_MODE_TX_RX;
	g_hUsart.Init.Parity = USART_PARITY_NONE;
	g_hUsart.Init.StopBits = USART_STOPBITS_1;
	g_hUsart.Init.WordLength = USART_WORDLENGTH_8B;

	ERR_CODE = HAL_USART_Init(&g_hUsart);

	return ERR_CODE;
}

void HAL_USART_MspInit(USART_HandleTypeDef *hUsart)
{
	if( hUsart->Instance == USARTx )
	{
		// Locals
		GPIO_InitTypeDef GPIO_InitStructure;

		/*## Enable peripherals and GPIO Clocks #################################*/
		/* Enable GPIO TX/RX clock */
		USART_GPIO_CLK_ENABLE();
		/* Enable USART clock */
		USART_RCC_CLK_ENABLE();
		/* Enable DMA clock */
		USART_DMA_CLK_ENABLE();

		/*## Configure peripheral GPIO ##########################################*/
		GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStructure.Pull = GPIO_PULLUP;
		GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
		GPIO_InitStructure.Alternate = GPIO_AF8_UART7;

		/* UART TX GPIO pin configuration  */
		GPIO_InitStructure.Pin = USART_TX_PIN;
		HAL_GPIO_Init(USART_TX_PORT, &GPIO_InitStructure);

		/* UART RX GPIO pin configuration  */
		GPIO_InitStructure.Pin = USART_RX_PIN;
		HAL_GPIO_Init(USART_RX_PORT,&GPIO_InitStructure);

		/*## Configure the DMA ##################################################*/
		// Prepare DMA for Rx struct
		g_hUsartRxDma.Instance = USART_RX_DMA_STREAM;
		g_hUsartRxDma.Init.Channel = USART_RX_DMA_CHANNEL;
		g_hUsartRxDma.Init.Direction = DMA_PERIPH_TO_MEMORY;
		g_hUsartRxDma.Init.PeriphInc = DMA_PINC_DISABLE;
		g_hUsartRxDma.Init.MemInc = DMA_MINC_ENABLE;
		g_hUsartRxDma.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		g_hUsartRxDma.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		g_hUsartRxDma.Init.Mode = DMA_NORMAL;
		g_hUsartRxDma.Init.Priority = DMA_PRIORITY_LOW;
		g_hUsartRxDma.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		g_hUsartRxDma.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		g_hUsartRxDma.Init.MemBurst = DMA_MBURST_SINGLE;
		g_hUsartRxDma.Init.PeriphBurst = DMA_PBURST_SINGLE;

		/* Initialize DMA */
		HAL_DMA_Init(&g_hUsartRxDma);

		/* Associate the initialized DMA handle to the the UART handle */
		__HAL_LINKDMA(hUsart, hdmarx, g_hUsartRxDma);

		/* Configure the DMA handler for Transmission process */
		g_hUsartTxDma.Instance = USART_TX_DMA_STREAM;
		g_hUsartTxDma.Init.Channel = USART_TX_DMA_CHANNEL;
		g_hUsartTxDma.Init.Direction = DMA_MEMORY_TO_PERIPH;
		g_hUsartTxDma.Init.PeriphInc = DMA_PINC_DISABLE;
		g_hUsartTxDma.Init.MemInc = DMA_MINC_ENABLE;
		g_hUsartTxDma.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		g_hUsartTxDma.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		g_hUsartTxDma.Init.Mode = DMA_NORMAL;
		g_hUsartTxDma.Init.Priority = DMA_PRIORITY_LOW;
		g_hUsartTxDma.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		g_hUsartTxDma.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		g_hUsartTxDma.Init.MemBurst = DMA_MBURST_SINGLE;
		g_hUsartTxDma.Init.PeriphBurst = DMA_MBURST_SINGLE;

		/* Initialize DMA */
		HAL_DMA_Init(&g_hUsartTxDma);

		/* Associate the initialized DMA handle to the the UART handle */
		__HAL_LINKDMA(hUsart, hdmatx, g_hUsartTxDma);

		/*## Configure the NVIC for DMA #########################################*/
		/* NVIC configuration for RX DMA transfer complete interrupt */
		HAL_NVIC_SetPriority(USART_DMA_RX_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(USART_DMA_RX_IRQn);

		/* NVIC configuration for TX DMA transfer complete interrupt */
		HAL_NVIC_SetPriority(USART_DMA_TX_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(USART_DMA_TX_IRQn);

		/*## Configure the NVIC for UART #########################################*/
		/* NVIC for SPI */
		HAL_NVIC_SetPriority(USART_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(USART_IRQn);
	}
}

void HAL_USART_MspDeInit(USART_HandleTypeDef *hUsart)
{
	if( hUsart->Instance == USARTx )
	{
    /*## Reset peripherals ##################################################*/
    USART_RCC_FORCE_RESET();
    USART_RCC_RELEASE_RESET();

    /*## Disable peripherals and GPIO Clocks ################################*/
    /* Deconfigure USART TX pin */
    HAL_GPIO_DeInit(USART_TX_PORT, USART_TX_PIN);
    /* Deconfigure USART TX port */
    HAL_GPIO_DeInit(USART_RX_PORT, USART_RX_PIN);

    /*## Disable the NVIC for USART ###########################################*/
    HAL_NVIC_DisableIRQ(USART_IRQn);
  }
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
