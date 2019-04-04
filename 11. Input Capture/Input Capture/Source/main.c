#include "stm32f10x.h"
#include "Usart_serial.h"
#include "stdio.h"


TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
NVIC_InitTypeDef 		NVIC_InitStructure;
GPIO_InitTypeDef  	GPIO_InitStructure;
EXTI_InitTypeDef  	EXTI_InitStructure;
TIM_OCInitTypeDef 	TIM_OCInitStructure;
TIM_ICInitTypeDef  TIM_ICInitStructure;

/* Private function prototypes -----------------------------------------------*/
void TIM4_PWM_Generation(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void TIM1_IC_Configuration (void);

int main(void)
{

  GPIO_Configuration();
  NVIC_Configuration();
	TIM4_PWM_Generation();
	TIM1_IC_Configuration();

  while (1)
		{

		}
}

void GPIO_Configuration(void)
	{
		/* PWM Generation - TIM2_CH1: PB9*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
			
		/* Input Capture - TIM1_CH1:PA8 */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	}

void TIM4_PWM_Generation(void)
	{
		/* Enable TIM4 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;														
  TIM_TimeBaseInitStructure.TIM_Period = 5000-1;												// 1000Hz														
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
																									
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				// clear on compare match
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;
	
	TIM_OCInitStructure.TIM_Pulse=2500-1;		
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM4, ENABLE);	
	}
	
void TIM1_IC_Configuration (void)
	{
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
	}
	
	void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM1 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}