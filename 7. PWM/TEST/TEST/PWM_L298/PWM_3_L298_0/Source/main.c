
/* Includes libraries ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"

/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
GPIO_InitTypeDef  	GPIO_InitStructure;
EXTI_InitTypeDef  	EXTI_InitStructure;
TIM_OCInitTypeDef 	TIM_OCInitStructure;

volatile int32_t debug;

/* Private functions prototypes ---------------------------------------------------------*/
void GPIO_Configuration(void);
void Direction_Configuration (void);
void TIM3_Configuration(void);
void Stop_Motor(void);

/*----------------------------------------------------------------------------------------*/
int main(void)
{ 
	GPIO_Configuration();
	Direction_Configuration();
	TIM3_Configuration();
  while (1)
  {
		GPIO_WriteBit(GPIOB, GPIO_Pin_6,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)));
		delay_ms(100);
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)==RESET)					// button 2
			{
				TIM_SetCompare3(TIM3,1250);
			}
			
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14)==RESET)					// button 3
			{
				TIM_SetCompare3(TIM3,3750);
			}
		
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)==RESET)					// button 4 -STOP MOTOR
				{
							Stop_Motor();
				}
	}
}	

void GPIO_Configuration(void)
{
	// Pin Input Buttons - PA11, PA12, PA14, PA15
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Pin Direction Configuration
		PA0: IN1
		PA1: IN2
	*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		// Pin PWM Configuration - ENABLE pin
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			//test pin PB7		
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
		
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
}

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

void Direction_Configuration (void)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)==RESET)					//button 1
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
			delay_ms(3000);
			GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);	
		}
		else
			{
				GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
				GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);	
			}
	}

void Stop_Motor(void)
	{
				GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
				GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);	
	}
	
/***********************************************************************/	