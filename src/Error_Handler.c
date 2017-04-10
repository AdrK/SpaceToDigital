/**
  ******************************************************************************
  * @file    Utils/Error_Handler.c
  * @author  Adrian Kurylak
  * @version V1.0.0
  * @date    25-November-2016
  * @brief   Simple handler of application errors
  ******************************************************************************
  */

#include "Error_Handler.h"

void Error_Handler(ERRCODE a_errCode)
{
	switch(a_errCode)
	{
		case ERROR_SYSTEM_INIT:
		{
			while(1){}
		}break;
		case ERROR_CONVERSION:
		{
			while(1){}
		}break;
		case ERROR_TRANSMIT:
		{
			while(1){}
		}break;
		case ERROR_GUI_INIT:
		{
			while(1){}
		}break;
		case ERROR_THREAD:
		{
			while(1){}
		}break;
		case ERROR_HARDFAULT:
		{
			while(1){}
		}break;
		case ERROR_HAL_INIT:
		{
			while(1){}
		}break;
		case ERROR_NMI:
		{
			while(1){}
		}break;
		case ERROR_GUI:
		default:
		{
			while(1){}
		}
	}
}

/**** END OF FILE ****/
