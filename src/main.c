/**
  ******************************************************************************
  * @file    main.c
  * @author  Adrian Kurylak
  * @version V1.0.0
  * @date    10-April-2017
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32746g_discovery.h"
#include "stm32f7xx.h"
#include "Error_Handler.h"
#include "Leds.h"
#include "stm32f7xx_USART.h"
#include "stm32f7xx_SPI.h"
#include "mpu9250.h"

static void SystemClock_Config(void);
void generate_triangle_data(uint8_t *data, uint16_t size);

int main(void)
{
	uint8_t DummyData[1024];
	uint8_t start[]="start\n";
	uint8_t stop[]="stop\n";
	uint16_t data16;
	uint8_t data8;

	HAL_Init();
	SystemClock_Config();
	Leds_Init();
	USART_Init();
	SPI_Init();

	generate_triangle_data(DummyData, 1024);

	while(1)
	{
		Led(LEDGREEN, 1);
		HAL_Delay(10);
		Led(LEDGREEN, 0);
		HAL_USART_Transmit_DMA(&g_hUsart,start,sizeof(start)-1);
		HAL_Delay(100);

		data16 = mpu_get_accel_x();
		HAL_USART_Transmit_DMA(&g_hUsart,(uint8_t*)&data16 , 2);
		HAL_Delay(10);

		data8 = '\n';
		HAL_USART_Transmit_DMA(&g_hUsart,(uint8_t*)&data8 , 1);
		HAL_Delay(10);

		data16 = mpu_get_accel_y();
		HAL_USART_Transmit_DMA(&g_hUsart, (uint8_t*)&data16, 2);
		HAL_Delay(10);

		data8 = '\n';
		HAL_USART_Transmit_DMA(&g_hUsart,(uint8_t*)&data8 , 1);
		HAL_Delay(10);

		data16 = mpu_get_accel_z();
		HAL_USART_Transmit_DMA(&g_hUsart, (uint8_t*)&data16, 2);
		HAL_Delay(10);

		data8 = '\n';
		HAL_USART_Transmit_DMA(&g_hUsart,(uint8_t*)&data8, 1);
		HAL_Delay(10);

		HAL_USART_Transmit_DMA(&g_hUsart,stop,sizeof(stop)-1);
		HAL_Delay(1000);
	}
	for(;;);
}

void generate_triangle_data(uint8_t *data, uint16_t size)
{
	int i=0;
	for (i = 0; i <= size; i++)
	{
			data[i]=i%255;
	}
}

static void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /**Configure the main internal regulator output voltage
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 10;
  RCC_OscInitStruct.PLL.PLLN = 210;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler(ERROR_SYSTEM_INIT);
  }

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler(ERROR_SYSTEM_INIT);
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler(ERROR_SYSTEM_INIT);
  }

    /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}
