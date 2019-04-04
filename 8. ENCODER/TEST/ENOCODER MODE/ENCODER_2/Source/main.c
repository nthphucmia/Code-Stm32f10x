
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

void PWM_Configuration(uint16_t pulse);
void Stop_Motor(void);
void Go_Straight(void);
void GPIO_Configuration (void);
void Test_BlinkingLed(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/*----------------------------------------------------------------------------------------*/
int main(void)
{ 			
	GPIO_Configuration();	
	GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_SET);
	while (1)
  {
					Go_Straight();
					if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)== Bit_RESET)				
						{
							GPIO_WriteBit(GPIOB, GPIO_Pin_7, 1^GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7));
							Stop_Motor();
						}
	}
}
	
void Test_BlinkingLed(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	delay_ms(50);
	GPIO_WriteBit(GPIOx, GPIO_Pin,(BitAction)(1^GPIO_ReadInputDataBit(GPIOx, GPIO_Pin)));
	delay_ms(50);
}
/***********************************************************************/	