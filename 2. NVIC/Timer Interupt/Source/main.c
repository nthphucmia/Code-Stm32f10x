
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"

GPIO_InitTypeDef  GPIO_InitStructure;
NVIC_InitTypeDef  NVIC_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

void GPIO_Configuration(void);
void TIM4_IT_Config(void);

int main(void)
{ 
	GPIO_Configuration();
	TIM4_IT_Config();
  while (1)
		{
		}
}
void GPIO_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/* Configure PB0 PB1 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
}
 
// Cau hinh ngat tran TIM4 sau moi 10s
void TIM4_IT_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	// TIM4 Configuration
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInitStructure.TIM_Period=100-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update); 			// clear update flag
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);  // enable Update interrupt 
	TIM_Cmd(TIM4, ENABLE); 											// enable timer 4
	
	// Enable the TIM4 global interrupt
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
