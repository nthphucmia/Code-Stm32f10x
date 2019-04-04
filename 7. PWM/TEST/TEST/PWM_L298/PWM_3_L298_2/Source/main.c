
/* Includes libraries ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"

#include "DC_Motor_Control.h"
#include "Encoder_Configuration.h"

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

/*----------------------------------------------------------------------------------------*/
int main(void)
{ 
	GPIO_Configuration();
	TIM4_Configuration();
  while (1)
  {
	}
}	

