/**
  ******************************************************************************
  * @file    Leds/Leds.h
  * @author  Adrian Kurylak
  * @version V1.0.0
  * @date    10-April-2017
  * @brief   HAL MSP module for UART
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_conf.h"
#include "stm32f7xx_UART.h"

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef g_hUart;
uint8_t g_UartTxBuffer[1024];
uint8_t g_UartRxBuffer[1024];
DMA_HandleTypeDef g_hUartTxDma;
DMA_HandleTypeDef g_hUartRxDma;

/* Private function prototypes -----------------------------------------------*/
HAL_StatusTypeDef UART_Init(void);
void HAL_UART_MspInit(UART_HandleTypeDef *hUsart);
void HAL_UART_MspDeInit(UART_HandleTypeDef *hUsart);

/* Private functions ---------------------------------------------------------*/

HAL_StatusTypeDef UART_Init(void)
{
	HAL_StatusTypeDef ERR_CODE;

	g_hUart.Instance = UARTx;
	g_hUart.Init.BaudRate = 9600;
	g_hUart.Init.Mode = UART_MODE_TX_RX;
	g_hUart.Init.Parity = UART_PARITY_NONE;
	g_hUart.Init.StopBits = UART_STOPBITS_1;
	g_hUart.Init.WordLength = UART_WORDLENGTH_8B;
	g_hUart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	g_hUart.AdvancedInit.MSBFirst = UART_ADVFEATURE_MSBFIRST_ENABLE;

	ERR_CODE = HAL_UART_Init(&g_hUart);

	return ERR_CODE;
}

void HAL_UART_MspInit(UART_HandleTypeDef *hUsart)
{
	if( hUsart->Instance == UARTx )
	{
		// Locals
		GPIO_InitTypeDef GPIO_InitStructure;

		/*##-1- Enable peripherals and GPIO Clocks #################################*/
		/* Enable GPIO TX/RX clock */
		UART_GPIO_CLK_ENABLE();
		/* Enable UART clock */
		UART_RCC_CLK_ENABLE();
		/* Enable DMA clock */
		UART_DMA_CLK_ENABLE();

		/*##-2- Configure peripheral GPIO ##########################################*/
		GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStructure.Pull = GPIO_PULLUP;
		GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
		GPIO_InitStructure.Alternate = GPIO_AF8_UART7;

		/* UART TX GPIO pin configuration  */
		GPIO_InitStructure.Pin = UART_TX_PIN;
		HAL_GPIO_Init(UART_TX_PORT, &GPIO_InitStructure);

		/* UART RX GPIO pin configuration  */
		GPIO_InitStructure.Pin = UART_RX_PIN;
		HAL_GPIO_Init(UART_RX_PORT,&GPIO_InitStructure);

		/*##-3- Configure the DMA ##################################################*/
		// Prepare DMA for Rx struct
		g_hUartRxDma.Instance = UART_RX_DMA_STREAM;
		g_hUartRxDma.Init.Channel = UART_RX_DMA_CHANNEL;
		g_hUartRxDma.Init.Direction = DMA_PERIPH_TO_MEMORY;
		g_hUartRxDma.Init.PeriphInc = DMA_PINC_DISABLE;
		g_hUartRxDma.Init.MemInc = DMA_MINC_ENABLE;
		g_hUartRxDma.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		g_hUartRxDma.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		g_hUartRxDma.Init.Mode = DMA_NORMAL;
		g_hUartRxDma.Init.Priority = DMA_PRIORITY_LOW;
		g_hUartRxDma.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		g_hUartRxDma.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		g_hUartRxDma.Init.MemBurst = DMA_MBURST_SINGLE;
		g_hUartRxDma.Init.PeriphBurst = DMA_PBURST_SINGLE;

		/* Initialize DMA */
		HAL_DMA_Init(&g_hUartRxDma);

		/* Associate the initialized DMA handle to the the UART handle */
		__HAL_LINKDMA(hUsart, hdmarx, g_hUartRxDma);

		/* Configure the DMA handler for Transmission process */
		g_hUartTxDma.Instance = UART_TX_DMA_STREAM;
		g_hUartTxDma.Init.Channel = UART_TX_DMA_CHANNEL;
		g_hUartTxDma.Init.Direction = DMA_MEMORY_TO_PERIPH;
		g_hUartTxDma.Init.PeriphInc = DMA_PINC_DISABLE;
		g_hUartTxDma.Init.MemInc = DMA_MINC_ENABLE;
		g_hUartTxDma.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		g_hUartTxDma.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		g_hUartTxDma.Init.Mode = DMA_NORMAL;
		g_hUartTxDma.Init.Priority = DMA_PRIORITY_LOW;
		g_hUartTxDma.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		g_hUartTxDma.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		g_hUartTxDma.Init.MemBurst = DMA_MBURST_SINGLE;
		g_hUartTxDma.Init.PeriphBurst = DMA_MBURST_SINGLE;

		/* Initialize DMA */
		HAL_DMA_Init(&g_hUartTxDma);

		/* Associate the initialized DMA handle to the the UART handle */
		__HAL_LINKDMA(hUsart, hdmatx, g_hUartTxDma);

		/*##-4- Configure the NVIC for DMA #########################################*/
		/* NVIC configuration for RX DMA transfer complete interrupt */
		HAL_NVIC_SetPriority(UART_DMA_RX_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(UART_DMA_RX_IRQn);

		/* NVIC configuration for TX DMA transfer complete interrupt */
		HAL_NVIC_SetPriority(UART_DMA_TX_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(UART_DMA_TX_IRQn);

		/*##-5- Configure the NVIC for UART #########################################*/
		/* NVIC for SPI */
		HAL_NVIC_SetPriority(UART_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(UART_IRQn);
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *hUsart)
{
	if( hUsart->Instance == UARTx )
	{
    /*##-1- Reset peripherals ##################################################*/
    UART_RCC_FORCE_RESET();
    UART_RCC_RELEASE_RESET();

    /*##-2- Disable peripherals and GPIO Clocks ################################*/
    /* Deconfigure UART TX pin */
    HAL_GPIO_DeInit(UART_TX_PORT, UART_TX_PIN);
    /* Deconfigure UART TX port */
    HAL_GPIO_DeInit(UART_RX_PORT, UART_RX_PIN);

    /*##-3- Disable the NVIC for USART ###########################################*/
    HAL_NVIC_DisableIRQ(UART_IRQn);
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
