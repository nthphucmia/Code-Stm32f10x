#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "DC_Motor_Control.h"

extern TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
extern NVIC_InitTypeDef 		NVIC_InitStructure;
extern GPIO_InitTypeDef  	GPIO_InitStructure;
extern EXTI_InitTypeDef  	EXTI_InitStructure;
extern TIM_OCInitTypeDef 	TIM_OCInitStructure;

void TIM4_Configuration(void)
{	
	/* Enable TIM4 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	// Direction, turn on motor
	GPIO_WriteBit(GPIOB, GPIO_Pin_14,1);
	GPIO_WriteBit(GPIOA, GPIO_Pin_10,0);
	
	// set speed
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;														
  TIM_TimeBaseInitStructure.TIM_Period = 5000-1;															
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
																										// enable timer 4	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				// clear on compare match
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;
	
	TIM_OCInitStructure.TIM_Pulse=3750-1;		//3599
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM4, ENABLE);	
}