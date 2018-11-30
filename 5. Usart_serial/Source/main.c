/**
VD: 
******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "usart_serial.h"

int main(void)
{ 
	USARTx_SendString(USART1,"Minh Ha Group - BanLinhKien.Vn");
//	sprintf(str,"\n\rDEMO USART\n\r");
//	USARTx_SendString(USART1,str);
  while (1)
  {

	}
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
