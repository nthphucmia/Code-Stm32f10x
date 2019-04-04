/********************************************************************************
 1. Use time1 with 4 channels to control 2 motors for PWM are TIM1_CH2, TIM1_CH2N, TIM1_CH3, TIM1_CH3N; frequency 1kHz. 
 2. Two encoders combined in motors have 2 phase A,B read by TIM2, TIM3, with interrupt configuration.
 3. TIM4 is interrupted every 10ms to calculate the velocity.
 4. The calculated velocity is printed in PC by UART with baud rate: 115200
 
 The connected diagramL
 STM32F103C8:
 PA2, PA3: Module UART 
 PA0, PA1: phase A, B encoder (motor1)
 PA6, PA7: phase A, B encoder (motor2)				
 PA9, PB14: upper and lower bridge driver motor1		// PA9: TIM1_CH2, PB14: TIM1_CH2N	
 PA10, PB15: upper and lower bridge driver motor12	// PA10: TIM1_CH3, PB15: TIM1_CH3N	
 PB9: LED display
*********************************************************************************/ 

/* Includes libraries ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_type.h"
#include "stm32f10x_it.h"
#include "delay.h"
#include "stdio.h"

GPIO_InitTypeDef  				GPIO_InitStructure;
NVIC_InitTypeDef 					NVIC_InitStructure;
TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
TIM_OCInitTypeDef					TIM_OCInitStructure;
TIM_ICInitTypeDef 				TIM_ICInitStructure;
USART_InitTypeDef					UART_InitStructure;

void PWM_Configuration(void);					// motor control
void Encoder_Configuration(void);
void Velocity_Calculate (void);


// Variable 
volatile uint16_t count_temp2, count_temp3;
//uint16_t CCW;
uint32_t encoder_pulse1, encoder_pulse2;
float count_recent1, count_recent2;
float count_update1, count_update2;
float motor_speed1, motor_speed2;
bool CCW=FALSE;
/*----------------------------------------------------------------------------------------------------------------*/
void PWM_Configuration(void);
void Encoder_Configuration(void);
void Encoder_reading (void);

int main(void)
{ 
	PWM_Configuration();
	Encoder_reading();
	Encoder_Configuration();
}

/* TIM1 Configuration for motor control*/
void PWM_Configuration(void)
{
	// Cap clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		
	/*	1.Configure PWM pin out TIM1 CH2- CH2N, CH3 - CH3N*/
	/* PWM pin A9, A10 configuration*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*PWM pin B14, B15 configuration*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*2. Timerbase Configuration*/
	/*Configure Frequency for PWM by: 72Mhz/(Period+1)/(Prescaler+1)=1KHz: */
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;				// TIM_CKD_DIV1((uint16_t)0x0000)
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period=5000-1;
	TIM_TimeBaseStructure.TIM_Prescaler=7200-1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	/*3. PWM Configuration*/
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;								// low-high, clear on compare match
	
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;
	
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;
		//TIM_OC2PolarityConfig(TIM1, TIM_OCPolarity_High);			// aready setup

	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;
	
	TIM_OCInitStructure.TIM_Pulse=2500-1;															//50%
	
	
	/*4. PWM Channel Configuration */
	/*PWM Channel 2*/
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
	TIM_OC2PreloadConfig(TIM1, ENABLE);											// Enable TIMx peripheral Preload register on CCR2	(Capture/Compare Register)	
	TIM_CCxCmd(TIM1, TIM_Channel_2, ENABLE); 								// Enable TIMx Capture Compare Channel
	TIM_CCxNCmd(TIM1, TIM_Channel_2, ENABLE);
	
	/*PWM Channel 3*/
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
	TIM_OC3PreloadConfig(TIM1, ENABLE);	
	TIM_CCxCmd(TIM1, TIM_Channel_3, ENABLE);
	TIM_CCxNCmd(TIM1, TIM_Channel_3, ENABLE); 
	//TIM_OC3NPolarityConfig(TIM1, TIM_OCPolarity_High);		// aready setup
	
	TIM_Cmd(TIM1, ENABLE); 																	// Enable TIM1
	TIM_CtrlPWMOutputs(TIM1, ENABLE);												// Enable TIM peripheral Main Outputs
}

/*TIM2, TIM3  Configuration for encoder reading*/
void Encoder_Configuration(void)
{
	/*Pin encoder configuration*/
	//	PA0, PA1: phase A, B encoder (motor1)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//PA6, PA7: phase A, B encoder (motor2)	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*----------Timer2 base configuration----------------------*/
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;				
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period=0xffff;
	TIM_TimeBaseStructure.TIM_Prescaler=0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_SetCounter(TIM2, 0);										//Reset Counter 1	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update); 			// clear update flag
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  // enable Update interrupt 
	TIM_Cmd(TIM2, ENABLE); 	
	
	/*-----------Timer3 base configuration----------------------*/
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;				
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period=0xffff;
	TIM_TimeBaseStructure.TIM_Prescaler=0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_SetCounter(TIM3, 0);										//Reset Counter 1
	TIM_ClearFlag(TIM3, TIM_FLAG_Update); 			// clear update flag
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);  // enable Update interrupt 
	TIM_Cmd(TIM3, ENABLE); 	
	
	/*-----------------Encoder  2 configuration---------------------*/
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;		// phase A, B
	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
	TIM_ICInitStructure.TIM_ICFilter=0x0f;
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	/*-----------------Encoder 3 configuration-----------------------*/
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
	TIM_ICInitStructure.TIM_ICFilter=0x0f;
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);

	/*Configures the TIM2 Encoder Interface*/
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI1, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
	
	/*Configures the TIM3 Encoder Interface*/
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI1, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);							//2 bits for pre-emption priority, 2 bits for subpriority

	// Enable the TIM2 global interrupt
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
	// Enable the TIM3 global interrupt
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

/*TIM4 is interrupted every 10ms to calculate the velocity.*/
void Encoder_reading (void)
	{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	// TIM4 Configuration
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision=0;
	TIM_TimeBaseStructure.TIM_Period=100-1;
	TIM_TimeBaseStructure.TIM_Prescaler=7200-1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update); 			// clear update flag
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);  // enable Update interrupt 
	TIM_Cmd(TIM4, ENABLE); 											// enable timer 4
	
	/* 2 bit for pre-emption priority, 2 bits for subpriority*/
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	// Enable the TIM4 global interrupt
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	}

void Direction_Determination (void)
	{
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==1)
		{
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==0)
			{CCW=FALSE;}
			else
			{CCW=TRUE;}
		}
	else
		{
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==0)
				{CCW=TRUE;}
			else
				{CCW=FALSE;}
		}
	}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
