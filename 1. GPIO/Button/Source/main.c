
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ADC_InitTypeDef ADC_InitStructure;
DMA_InitTypeDef DMA_InitStructure;
GPIO_InitTypeDef  GPIO_InitStructure;

void GPIO_Configuration(void);

/* Private functions ---------------------------------------------------------*/

int main(void)
{ 
	GPIO_Configuration();
	GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_SET);
  while (1)
  {
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)== Bit_RESET)
		{
			GPIO_WriteBit(GPIOB, GPIO_Pin_7, 1^GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7));
		}
	}
}

void GPIO_Configuration(void)
{
		/* MODE INPUT */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;								// button 4		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  
		
		/*Mode OUTPUT */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7				;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 				
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
}
 