#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "DC_Motor_Control.h"
#include "delay.h"

//Direction
#define CW 	0
#define CCW 1

extern TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
extern NVIC_InitTypeDef 		NVIC_InitStructure;
extern GPIO_InitTypeDef  	GPIO_InitStructure;
extern EXTI_InitTypeDef  	EXTI_InitStructure;
extern TIM_OCInitTypeDef 	TIM_OCInitStructure;

 /**TIM3 GPIO Configuration    
    PB0     ------> TIM3_CH3
    */
void TIM3_Configuration(void)
{	
	/* Enable TIM3 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		
	// set speed
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;														
  TIM_TimeBaseInitStructure.TIM_Period = 5000-1;															
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;								// clear on compare match
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;
	
	TIM_OCInitStructure.TIM_Pulse=2500-1;														//50% PWM
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM3, ENABLE);	
}

void Direction_Configuration (unsigned char Direction)
	{
		switch(Direction)
			{
				case CW:
						GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
						delay_ms(3000);
						GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
				break;
				
				case CCW:
						GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
						delay_ms(3000);
						GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
				break;
			}
	}

void Stop_Motor(void)
	{
				GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
				GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);	
	}