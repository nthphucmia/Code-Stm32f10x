/**
  ******************************************************************************
  * Ten Tep		:		    user_interrupt.c
  * Tac Gia		:	  		Nguyen Quy Nhat
  * Cong Ty		:			MinhHaGroup
  *	Website 	:			MinhHaGroup.com
  * Phien Ban	:			V1.0.0
  * Ngay		:    		31-07-2012
  * Tom Tat		:       	Dinh nghia cac ham con phuc vu ngat.
  *             			
  *           
  *
  ******************************************************************************
  * Chu Y			:				
  *
  *
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "Usart_serial.h"
#include "User_interrupt.h"

extern uint32_t  NumberPulse;
extern uint32_t  Frequency;
extern uint16_t  CurrentValue;
extern uint16_t  LastValue;

void TIM1_UP_IRQHandler(void)
{
  /* Clear the TIM1 Update pending bit */
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
		{
			//USARTx_SendString(USART2,"TIM1_UP_IRQHandler");	
			TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
			NumberPulse+=0xffff;
    }
}

void TIM1_CC_IRQHandler(void)
{
		if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
		{
			USARTx_SendString(USART2,"TIM1_CC_IRQHandler");	
			TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
			CurrentValue  =  TIM_GetCapture1(TIM1);
			Frequency     =  NumberPulse+CurrentValue-LastValue;
			NumberPulse   =  0;
			LastValue     =  CurrentValue;
				
    }
}
/******************* (C) COPYRIGHT 2012 MinhHaGroup *****END OF FILE****/
