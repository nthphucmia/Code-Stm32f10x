	/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "usart_serial.h"
#include "stdio.h"
#include "delay.h"


uint8_t data=10 ;
uint8_t test=10;
int main(void)
{
	char str[50];
	GPIO_USART_Configuration();
	USARTx_Configuration(USART1);

  while (1)
  {
		test=test+1;
//		USARTx_SendChar(USART1, test);
		USARTx_SendString(USART1,"Minh Ha Group - BanLinhKien.Vn - Test\n\r");	
//		sprintf(str,"\n\rDEMO USART\n\r");
//		USARTx_SendString(USART3,str);
//		printf("Xin chao cac ban %d lan \n ",data);
			delay_ms(100);
  }
}
