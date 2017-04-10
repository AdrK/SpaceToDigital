/**
  ******************************************************************************
  * @file    Leds/Leds.h
  * @author  Adrian Kurylak
  * @version V1.0.0
  * @date    10-April-2017
  * @brief   Header for leds configuration file
  ******************************************************************************
  */

#ifndef __LEDS_H
#define __LEDS_H

typedef enum LEDS{
	LEDGREEN,
}LEDS;

/* Definition for Pins */
#define LEDGREEN_PIN						GPIO_PIN_1

#define LEDGREEN_GPIO_PORT					GPIOI

#define LEDGREEN_GPIO_CLK_ENABLE();			__HAL_RCC_GPIOI_CLK_ENABLE();

HAL_StatusTypeDef Leds_Init(void);
HAL_StatusTypeDef Leds_DeInit(void);
void Led(LEDS a_Led,uint8_t a_State);
//void Leds_Binary(uint8_t a_u8_Value);
//void Leds_All_On(void);
//void Leds_All_Off(void);

#endif /* __LEDS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
