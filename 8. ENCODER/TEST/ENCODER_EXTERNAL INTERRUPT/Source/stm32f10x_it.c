
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "delay.h"

int counter_pulse;

void EXTI9_5_IRQHandler(void)
{
if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
		counter_pulse++; 
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}
