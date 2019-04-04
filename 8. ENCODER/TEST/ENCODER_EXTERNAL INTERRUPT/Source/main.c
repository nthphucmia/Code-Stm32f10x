
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"

GPIO_InitTypeDef  GPIO_InitStructure;
EXTI_InitTypeDef  EXTI_InitStructure;
NVIC_InitTypeDef  NVIC_InitStructure;

void GPIO_Configuration(void);
void EXTI9_5_Configuration(void);
void Test_BlinkingLed(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

int main(void)
{ 
	GPIO_Configuration();
	EXTI9_5_Configuration();
  while (1)
  {
		//Test_BlinkingLed(GPIOB, GPIO_Pin_3);
	}
}
void GPIO_Configuration(void)
{
	/*----------------------PORT B----------------------------*/	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 				
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
}
 
// PA6, PA7
void EXTI9_5_Configuration(void)
	{
		//cap clock cho ngat ngoai va ngoai vi
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOA, &GPIO_InitStructure);		
		/* mapping */
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);
		/* Clear the the EXTI line interrupt pending bit */
		EXTI_ClearITPendingBit(EXTI_Line6);
		/*EXTI line Configuration */
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Line = EXTI_Line6;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
		
				/*NVIC Configuration*/
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}
	

void Test_BlinkingLed(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	delay_ms(50);
	GPIO_WriteBit(GPIOx, GPIO_Pin,(BitAction)(1^GPIO_ReadInputDataBit(GPIOx, GPIO_Pin)));
	delay_ms(50);
}

