#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"
#include "GPIO_Configuration.h"

extern GPIO_InitTypeDef  	GPIO_InitStructure;

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
		PA3: ENABLE PIN
		Pin PWM Configuration
	 */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
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


