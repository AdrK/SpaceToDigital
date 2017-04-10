/**
  ******************************************************************************
  * @file    DAC/DAC_Config.h
  * @author  Adrian Kurylak
  * @version V1.0.0
  * @date    25-November-2016
  * @brief   Header for error handler file
  ******************************************************************************
  */

#ifndef __ERROR_HANDLER_H
#define __ERROR_HANDLER_H

typedef enum ERRCODE{
	ERROR_SYSTEM_INIT,
	ERROR_CONVERSION,
	ERROR_TRANSMIT,
	ERROR_THREAD,
	ERROR_HARDFAULT,
	ERROR_MEMMANAGE,
	ERROR_BUSFAULT,
	ERROR_USAGEFAULT,
	ERROR_DEBUGMON,
	ERROR_HAL_INIT,
	ERROR_GUI_INIT,
	ERROR_GUI,
	ERROR_NMI
}ERRCODE;

void Error_Handler(ERRCODE a_errCode);

#endif /* __ERROR_HANDLER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
