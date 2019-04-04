#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"
#include "Input_Capture.h"

extern TIM_ICInitTypeDef  				TIM_ICInitStructure;
extern TIM_TimeBaseInitTypeDef 		TIM_TimeBaseInitStructure;
extern NVIC_InitTypeDef 					NVIC_InitStructure;
extern GPIO_InitTypeDef  					GPIO_InitStructure;

void Input_Capture_TIM1_Configuration (void)
	{
		/* Input Capture - TIM1_CH1:PA8 */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		
		/*----------------------------Timer1 base configuration-------------------------------------*/
		TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;				
		TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInitStructure.TIM_Period=0xffff;
		TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;	
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure); 
		
		/*----------------------------Input Capture Configuration-------------------------------------*/
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
		TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
		TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
		TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
		TIM_ICInitStructure.TIM_ICFilter = 0x05;
		TIM_ICInit(TIM1, &TIM_ICInitStructure);
		
		/* TIM enable counter */
		TIM_Cmd(TIM1, ENABLE);

	/* Enable the CC1 Interrupt Request */
		TIM_ClearFlag(TIM1, TIM_FLAG_Update); 			// clear update flag
		TIM_ITConfig(TIM1,TIM_IT_CC1,ENABLE);				
		TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
		
		/* Enable the TIM1 global Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}

unsigned short icValue=0;
unsigned short count=0;
unsigned short preValue=0;
unsigned short T=0;
unsigned long f=0;

void TIM1_CC_IRQHandler(void)																						// TIM1 UP Interrupt
{
				if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)									
		{
				TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
				count=count+1;
			  icValue  =  TIM_GetCapture1(TIM1);
				T=icValue-preValue;
				preValue=icValue;
				f=10000/T		;								// f=clock_frequency/T (clock frequency=72000000/7200 (prescaler=7200)
    }
}	