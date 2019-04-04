#include "stm32f10x.h"
#include "DC_Motor_Control.h"
#include "delay.h"

extern TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
extern NVIC_InitTypeDef 			NVIC_InitStructure;
extern GPIO_InitTypeDef  	GPIO_InitStructure;
extern EXTI_InitTypeDef  	EXTI_InitStructure;
extern TIM_OCInitTypeDef 	TIM_OCInitStructure;

extern uint16_t rate, actual_speed, desired_speed;

 /**
	TIM3 GPIO Configuration    
  PA2     ------> TIM2
  **/
void PWM_Configuration(uint16_t pulse)
{	
	/* Enable TIM2 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitStructure.TIM_Prescaler = 9-1;						// tan so 1000 Hz								
  TIM_TimeBaseInitStructure.TIM_Period = 8000-1;															
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
																										
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;
	
	TIM_OCInitStructure.TIM_Pulse=pulse-1;		
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);								// TIM2_CH3		
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM2, ENABLE);
}	


void Motor_control (uint16_t set_speed)
	{
		uint16_t desired_pulse;
		desired_speed=set_speed;
		desired_pulse=(set_speed*100)/(320);			// maximum speed 
		Run_Motor(desired_pulse);
	}

	/*
	 1. The motor run when
		BRA: Low
		PWM: High
		DIR: High or Low
	  
		2. The motor stop (without brake) when
		PWM: Low
		BRA: Low
		DIR: X
	
		3. The motor stop (with brake) when
		PWM, DIR, BRA: High
		PWM, BRA: High		and DIR: Low
		PWM: Low and DIR (X), Brake: High
		-------------------------------------
		|				PA2: PWM										|			
		|				PA0:	BRAKE									|
		|				PA1: 	DIR									  |
		-------------------------------------
	*/
	
void Run_Motor (uint16_t pulse)
	{
			// turn on the motor
		  GPIO_SetBits(GPIOA, GPIO_Pin_2);
			GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		
			// direction determination
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		
			//set speed
			PWM_Configuration(pulse);
	}

void Stop_Motor_no_BRA(void)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_0| GPIO_Pin_2);
	}