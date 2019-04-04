#include "User_interrupt.h"

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"
#include "User_interrupt.h"
#include "Usart_serial.h"
#include "GPIO_Configuration.h"

extern uint32_t  NumberPulse;
extern uint32_t  Counter_pulse;
extern uint16_t  CurrentValue;
extern uint16_t  LastValue;
				uint16_t Pre_pulse=0;
				uint16_t Pulse=0;
extern	uint16_t encoderSpeed;
extern	uint16_t Pulse_value;

void TIM1_UP_IRQHandler(void)
{
  /* Clear the TIM1 Update pending bit */
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
		{
				TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
			  NumberPulse+=0xffff;
    }
}

void TIM1_CC_IRQHandler(void)
{
		if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
		{
				TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
			  CurrentValue  =  TIM_GetCapture1(TIM1);
			  Counter_pulse =  NumberPulse+CurrentValue-LastValue;
			  NumberPulse   =  0;
			  LastValue     =  CurrentValue;
    }
}

// calculate the feedback speed back every 10ms
void TIM4_IRQHandler(void)
{
				Pre_pulse = Counter_pulse;  
        Pulse_value = (float)(Pulse-Pre_pulse);
        //encoderSpeed=(float)(((pulse_value)/400)/(time_interval)*60000;			// encoder do phan giai 400 xung
        delay_ms(100);
        Pulse = Pre_pulse;
	      Pulse=0; 
        Counter_pulse=0;
}