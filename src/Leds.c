/**
  ******************************************************************************
  * @file    Leds/Leds.h
  * @author  Adrian Kurylak
  * @version V1.0.0
  * @date    10-April-2017
  * @brief   Leds configuration
  ******************************************************************************
  */

/******** Pin config ********/
/****************************/
/*********** LED1  **********/
/*********** PA0 ************/
/****************************/

#include "stm32f7xx_hal.h"
#include "Leds.h"

HAL_StatusTypeDef Leds_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	LEDGREEN_GPIO_CLK_ENABLE();

	GPIO_InitStructure.Pin = LEDGREEN_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(LEDGREEN_GPIO_PORT,&GPIO_InitStructure);

	return HAL_OK;
}

HAL_StatusTypeDef Leds_DeInit(void)
{
	HAL_GPIO_DeInit(LEDGREEN_GPIO_PORT,LEDGREEN_PIN);

	return HAL_OK;
}

void Led(LEDS a_Led,uint8_t a_State)
{
	switch(a_Led)
	{
		case LEDGREEN:
		{
			HAL_GPIO_WritePin(LEDGREEN_GPIO_PORT, LEDGREEN_PIN,(a_State ? GPIO_PIN_SET : GPIO_PIN_RESET));
		}break;
	}
}
/*
void Leds_Binary(uint8_t a_u8_Value)
{
	a_u8_Value = a_u8_Value << 4;

	Led(LEDRED1,a_u8_Value & 0x80);
	Led(LEDRED2,a_u8_Value & 0x40);
	Led(LEDRED3,a_u8_Value & 0x20);
	Led(LEDBLUE,a_u8_Value & 0x10);
}

void Leds_All_On()
{
	Leds_Binary(1);
}

void Leds_All_Off()
{
	Leds_Binary(0);
}
*/
/**** END OF FILE ****/
