#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#include "stdio.h"
#include "Usart_serial.h"
#include "User_interrupt.h"
#include "GPIO_Configuration.h"
#include "Encoder_Configuration.h"
#include "DC_Motor_Control.h"
#include "stm32f10x_type.h"
#include "stdio.h"
#include "PID_control.h"

bool CCW=FALSE;		
volatile uint32_t timer3_cnt_ovr=0;

void TIM3_IRQHandler(void)																
{	
 if(TIM_GetITStatus( TIM3,TIM_IT_Update)!=RESET) 				// ngat khi tran
		{
			TIM_ClearFlag(TIM3, TIM_IT_Update);
			timer3_cnt_ovr++;		
    }
}

void TIM4_IRQHandler(void)
{	
 if(TIM_GetITStatus( TIM4,TIM_IT_Update)!=RESET) 
 {
		 TIM_ClearFlag(TIM4, TIM_IT_Update);
		 Encoder_Reading();	
		 Motor_Speed_PID(300);
 }
}

