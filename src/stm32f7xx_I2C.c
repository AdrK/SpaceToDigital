/**
  ******************************************************************************
  * @file    src/stm32f7xx_I2C.c
  * @author  Adrian Kurylak
  * @version V1.0.0
  * @date    10-April-2017
  * @brief   HAL MSP module for I2C
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32f7xx_I2C.h"

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef g_hI2c;
uint8_t g_I2c_Buffer[1024];
DMA_HandleTypeDef g_I2cTxDma, g_I2ctRxDma;

/* Private function prototypes -----------------------------------------------*/
HAL_StatusTypeDef I2C_Init(void);
void HAL_I2C_MspInit(I2C_HandleTypeDef *hI2c);
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hI2c);

/* Private functions ---------------------------------------------------------*/
HAL_StatusTypeDef I2C_Init(void)
{
	HAL_StatusTypeDef ERR_CODE;

	g_hI2c.Instance = I2Cx;
	g_hI2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	g_hI2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	g_hI2c.Init.GeneralCallMode = I2C_GENERALCALL_ENABLE;
	g_hI2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	g_hI2c.Init.OwnAddress1 = 0;
	g_hI2c.Init.OwnAddress2 = 0;
	g_hI2c.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	g_hI2c.Init.Timing = 0x00A0A3F7;

	ERR_CODE = HAL_I2C_Init(&g_hI2c);

	return ERR_CODE;
}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hI2c)
{
	if( hI2c->Instance == I2Cx )
	{
		// Locals
		GPIO_InitTypeDef GPIO_InitStructure;

		/*##-1- Enable peripherals and GPIO Clocks #################################*/
		/* Enable GPIO TX/RX clock */
		I2C_GPIO_CLK_ENABLE();
		/* Enable I2C clock */
		I2C_RCC_CLK_ENABLE();
		/* Enable DMA clock */
		I2C_DMA_CLK_ENABLE();

		/*##-2- Configure peripheral GPIO ##########################################*/
		GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStructure.Pull = GPIO_PULLUP;
		GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
		GPIO_InitStructure.Alternate = GPIO_AF4_I2C1;

		/* I2C SCL GPIO pin configuration  */
		GPIO_InitStructure.Pin = I2C_SCL_PIN;
		HAL_GPIO_Init(I2C_SCL_PORT, &GPIO_InitStructure);

		/* I2C SDA GPIO pin configuration  */
		GPIO_InitStructure.Pin = I2C_SDA_PIN;
		HAL_GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);

		/*##-3- Configure the DMA ##################################################*/
		// Prepare DMA for Rx struct
		g_I2ctRxDma.Instance = I2C_DMA_RX_STREAM;
		g_I2ctRxDma.Init.Channel = I2C_DMA_RX_CHANNEL;
		g_I2ctRxDma.Init.Direction = DMA_PERIPH_TO_MEMORY;
		g_I2ctRxDma.Init.PeriphInc = DMA_PINC_DISABLE;
		g_I2ctRxDma.Init.MemInc = DMA_MINC_ENABLE;
		g_I2ctRxDma.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		g_I2ctRxDma.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		g_I2ctRxDma.Init.Mode = DMA_NORMAL;
		g_I2ctRxDma.Init.Priority = DMA_PRIORITY_LOW;
		g_I2ctRxDma.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		g_I2ctRxDma.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		g_I2ctRxDma.Init.MemBurst = DMA_MBURST_SINGLE;
		g_I2ctRxDma.Init.PeriphBurst = DMA_PBURST_SINGLE;

		/* Initialize DMA */
		HAL_DMA_Init(&g_I2ctRxDma);

		/* Associate the initialized DMA handle to the the I2C handle */
		__HAL_LINKDMA(hI2c, hdmarx, g_I2ctRxDma);

		/* Configure the DMA handler for Transmission process */
		g_I2cTxDma.Instance = I2C_DMA_TX_STREAM;
		g_I2cTxDma.Init.Channel = I2C_DMA_TX_CHANNEL;
		g_I2cTxDma.Init.Direction = DMA_MEMORY_TO_PERIPH;
		g_I2cTxDma.Init.PeriphInc = DMA_PINC_DISABLE;
		g_I2cTxDma.Init.MemInc = DMA_MINC_ENABLE;
		g_I2cTxDma.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		g_I2cTxDma.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		g_I2cTxDma.Init.Mode = DMA_NORMAL;
		g_I2cTxDma.Init.Priority = DMA_PRIORITY_LOW;
		g_I2cTxDma.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		g_I2cTxDma.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		g_I2cTxDma.Init.MemBurst = DMA_MBURST_SINGLE;
		g_I2cTxDma.Init.PeriphBurst = DMA_MBURST_SINGLE;

		/* Initialize DMA */
		HAL_DMA_Init(&g_I2cTxDma);

		/* Associate the initialized DMA handle to the the I2C handle */
		__HAL_LINKDMA(hI2c, hdmatx, g_I2cTxDma);

		/*##-4- Configure the NVIC for DMA #########################################*/
		/* NVIC configuration for RX DMA transfer complete interrupt */
		HAL_NVIC_SetPriority(I2C_DMA_RX_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(I2C_DMA_RX_IRQn);

		/* NVIC configuration for TX DMA transfer complete interrupt */
		HAL_NVIC_SetPriority(I2C_DMA_TX_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(I2C_DMA_TX_IRQn);

	    /*##-5- Reset peripheral ##################################################*/
	    I2C_RCC_FORCE_RESET();
	    I2C_RCC_RELEASE_RESET();

	}
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hI2c)
{
	if( hI2c->Instance == I2Cx )
	{
    /*##-1- Reset peripheral ##################################################*/
    I2C_RCC_FORCE_RESET();
    I2C_RCC_RELEASE_RESET();

    /*##-2- Disable peripherals and GPIO Clocks ################################*/
    /* Deconfigure I2C SCL pin */
    HAL_GPIO_DeInit(I2C_SCL_PORT, I2C_SCL_PIN);
    /* Deconfigure I2C SDA port */
    HAL_GPIO_DeInit(I2C_SDA_PORT, I2C_SDA_PIN);

  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
