
/* Includes libraries ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"

/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
GPIO_InitTypeDef  	GPIO_InitStructure;
EXTI_InitTypeDef  	EXTI_InitStructure;
TIM_OCInitTypeDef 	TIM_OCInitStructure;

/* Private functions prototypes ---------------------------------------------------------*/
void PWM_Configuration(void);
void Stop_Motor(void);
void Go_Straight(void);
void GPIO_Configuration (void);
void Test_BlinkingLed(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/*----------------------------------------------------------------------------------------*/
int main(void)
{ 			
	GPIO_Configuration();	
	while (1)
  {
			Go_Straight();
			Test_BlinkingLed(GPIOB, GPIO_Pin_7);
	}
}
 void GPIO_Configuration (void)
 {	 
	 /* Pin Direction Configuration
		PA0: IN1
		PA1: IN2
		*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
			 
		/* 
		PB9: ENABLE PIN
		Pin PWM Configuration
	 */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		//test pin PB7	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		//test pin PC13
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
 }
 /**
	TIM3 GPIO Configuration    
  PB0     ------> TIM3_CH3
  **/
void PWM_Configuration(void)
{	
	/* Enable TIM4 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;														
  TIM_TimeBaseInitStructure.TIM_Period = 5000-1;															
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
																										
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;
	
	TIM_OCInitStructure.TIM_Pulse=3750-1;		//3599
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM4, ENABLE);
}	

void Go_Straight (void)
	{
			// turn on the motor
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
			GPIO_ResetBits(GPIOA, GPIO_Pin_3);	
			//set speed
			PWM_Configuration();
			delay_ms(2000);
			// turn off motor
			Stop_Motor();
	}

void Stop_Motor(void)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2| GPIO_Pin_3);
	}
	
void Test_BlinkingLed(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	delay_ms(50);
	GPIO_WriteBit(GPIOx, GPIO_Pin,(BitAction)(1^GPIO_ReadInputDataBit(GPIOx, GPIO_Pin)));
	delay_ms(50);
}
/***********************************************************************/	