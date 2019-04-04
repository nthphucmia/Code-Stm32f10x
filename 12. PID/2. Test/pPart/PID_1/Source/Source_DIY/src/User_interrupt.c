#include "User_interrupt.h"
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"
#include "User_interrupt.h"
#include "Usart_serial.h"
#include "GPIO_Configuration.h"
#include "stm32f10x_type.h"
#include "stdio.h"

#include "stm32f10x.h"                  // Device header
int CCW=FALSE;
int Direction;
extern uint32_t encoder_cnt_pulse, encoder_cnt_pulse_pre;
extern uint32_t rate, actual_speed;
char str[50]; 

//void TIM1_CC_IRQHandler(void)																						// TIM1 Capture Compare Interrupt
//{
//		if (TIM_GetITStatus(TIM1, TIM_IT_CC1) == SET)
//		{
//			TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
//			Pulse=Pulse++;
//			encoder_cnt=TIM_GetCounter(TIM1);
//			rate=(encoder_cnt-encoder_cnt_pre)/400;
//			encoder_cnt_pre=encoder_cnt;
//    }
//}


void TIM4_IRQHandler (void)
{	
 if(TIM_GetITStatus( TIM4,TIM_IT_Update)!=RESET) //if update flag turns on
 {
		 TIM_ClearFlag(TIM4, TIM_FLAG_Update); //clear update flag
		 GPIO_WriteBit(GPIOC,GPIO_Pin_13,(BitAction)(1^GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)));
     encoder_cnt_pulse=TIM_GetCounter(TIM1);
			if(encoder_cnt_pulse>encoder_cnt_pulse_pre)
				{
					rate=(encoder_cnt_pulse-encoder_cnt_pulse_pre);
				}
			else if (encoder_cnt_pulse_pre>encoder_cnt_pulse)
				{
					rate=(encoder_cnt_pulse_pre-encoder_cnt_pulse);
				}
			else { rate=0;}
			actual_speed=(rate*6000)/400;
		  encoder_cnt_pulse_pre=encoder_cnt_pulse;
 }
}


void Direction_Determination (void)
	{		
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)==1)
		{
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==0)
			{ CCW=TRUE;}
			{	CCW=FALSE;}
		}
	else
		{
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==0)
				{CCW=FALSE;}
			else
				{CCW=TRUE;}
		}
		
// Direction Test
		if(CCW==TRUE)
			{
			  sprintf(str,"\n\rCCW\n\r");
				USARTx_SendString(USART2,str);
			}
  else
		{
				 sprintf(str,"\n\rCW\n\r");
				USARTx_SendString(USART2,str);
		}
	}
	

