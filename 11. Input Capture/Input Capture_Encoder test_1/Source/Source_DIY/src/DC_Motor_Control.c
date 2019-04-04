//#include "stm32f10x.h"
//#include "stm32f10x_it.h"
//#include "DC_Motor_Control.h"
//#include "delay.h"

//extern TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//extern NVIC_InitTypeDef 		NVIC_InitStructure;
//extern GPIO_InitTypeDef  	GPIO_InitStructure;
//extern EXTI_InitTypeDef  	EXTI_InitStructure;
//extern TIM_OCInitTypeDef 	TIM_OCInitStructure;


//void PWM_Configuration(uint16_t pulse)
//{	
//	/* Enable TIM2 clock */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

//	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;						// tan so 1000 Hz								
//  TIM_TimeBaseInitStructure.TIM_Period = 10-1;															
//	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
//	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
//																										
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				
//	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;
//	
//	TIM_OCInitStructure.TIM_Pulse=pulse-1;		
//	TIM_OC3Init(TIM2, &TIM_OCInitStructure);								// TIM2_CH3		
//	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
//	
//	TIM_Cmd(TIM2, ENABLE);
//}	

//void Go_Straight (void)
//	{
//			// turn on the motor
//			GPIO_SetBits(GPIOA, GPIO_Pin_1);
//			GPIO_ResetBits(GPIOA, GPIO_Pin_0);
//			//set speed
//			PWM_Configuration(5);
//			delay_ms(2000);
//	}

//void Stop_Motor(void)
//	{
//		GPIO_ResetBits(GPIOA, GPIO_Pin_0| GPIO_Pin_1);
//	}