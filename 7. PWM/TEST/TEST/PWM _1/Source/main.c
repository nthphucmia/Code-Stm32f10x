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

int main(void)
{ 
	SysTick_Config(SystemCoreClock/1000);
	PWM_Configuration();
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
	
	TIM_Cmd(TIM1, ENABLE); 																	// Enable TIM1
	TIM_CtrlPWMOutputs(TIM1, ENABLE);												// Enable TIM peripheral Main Outputs
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
