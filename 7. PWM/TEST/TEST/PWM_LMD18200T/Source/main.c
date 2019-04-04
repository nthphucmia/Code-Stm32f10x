/********************************************************************************
 1. Use time1 with 4 channels to control 2 motors for PWM are TIM1_CH2, TIM1_CH2N, TIM1_CH3, TIM1_CH3N; frequency 1kHz. 
 2. Two encoders combined in motors have 2 phase A,B read by TIM2, TIM3, with interrupt configuration.
 3. TIM4 is interrupted every 10ms to calculate the velocity.
 4. The calculated velocity is printed in PC by UART with baud rate: 115200
 
 The conneWcted diagramL
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
#include "stm32f10x_it.h"
#include "delay.h"

/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
NVIC_InitTypeDef 		NVIC_InitStructure;
GPIO_InitTypeDef  	GPIO_InitStructure;
EXTI_InitTypeDef  	EXTI_InitStructure;
TIM_OCInitTypeDef 	TIM_OCInitStructure;

volatile int32_t debug;

/* Private functions prototypes ---------------------------------------------------------*/
void GPIO_Configuration(void);
void TIM4_Configuration(void);
void TIM2_Configuration(void);
void Direction_Configuration (void);

/*----------------------------------------------------------------------------------------*/
int main(void)
{ 
	GPIO_Configuration();
	Direction_Configuration();
	TIM4_Configuration();
	
  while (1)
  {
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==RESET)					// Change direction of motor
			{
				GPIO_WriteBit(GPIOB, GPIO_Pin_14,Bit_RESET);
				GPIO_WriteBit(GPIOA, GPIO_Pin_10,Bit_SET);
			}
			
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)==RESET)
			{
				 TIM_SetCompare3(TIM3,1250);											// 25%
			}
			
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_14)==RESET)
			{
				TIM_SetCompare3(TIM3,2500);		
			}		
	}
}	

void GPIO_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// Pin Input Button Configuration
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;																			// pull-up resitor
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// Pin Direction Configuration 
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
			  
    /**TIM3 GPIO Configuration    
    PB0     ------> TIM3_CH3
    */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
}

void TIM3_Configuration(void)
{	
	/* Enable TIM3 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		
	// set speed
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;														
  TIM_TimeBaseInitStructure.TIM_Period = 5000-1;															
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
																										
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				// clear on compare match
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;
	
	TIM_OCInitStructure.TIM_Pulse=3750-1;										// 75%
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM3, ENABLE);	
}

void Direction_Configuration (void)
	{
		/*
			PA9, PB14: upper and lower bridge driver motor1
			Start motor clock wise rotation/counter clock wise rotation
		*/
		GPIO_WriteBit(GPIOB, GPIO_Pin_14,Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_10,Bit_RESET);
	}

