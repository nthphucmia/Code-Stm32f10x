#include "User_interrupt.h"
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"
#include "User_interrupt.h"
#include "Usart_serial.h"
#include "GPIO_Configuration.h"
#include "stm32f10x_type.h"
#include "stdio.h"

bool CCW=FALSE;

extern uint32_t  NumberPulse;
extern uint32_t  Counter_pulse;
extern uint16_t  CurrentValue;
extern uint16_t  LastValue;
				uint16_t timer1_temp=0;
				uint16_t count_temp=0;
extern	uint16_t encoderSpeed;
extern	uint16_t Pulse_value;

extern uint16_t encoder_cnt, encoder_cnt_pre;
extern uint16_t rate, motor_speed;
char str[50]; 
unsigned short icValue=0;
unsigned short count=0;
unsigned short preValue=0;
unsigned short T=0;
unsigned long f=0;
unsigned long time_interval;

unsigned int frequency;

	void TIM3_IRQHandler(void)																// TIM UPDATE
{
		if (TIM_GetFlagStatus(TIM3, TIM_FLAG_Update) == SET)
		{
			TIM_ClearFlag(TIM3, TIM_FLAG_Update);
			timer1_temp = TIM3->CNT;	
			if (timer1_temp == 65535) count_temp--	;
			if (timer1_temp == 0)			count_temp++;
    }
}


//void TIM4_IRQHandler(void)
//{	
// if(TIM_GetITStatus( TIM4,TIM_IT_Update)!=RESET) 
// {
//		 TIM_ClearFlag(TIM4, TIM_IT_Update); 
//		 GPIO_WriteBit(GPIOC,GPIO_Pin_13,(BitAction)(1^GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))); 	 
//		 encoder_cnt=TIM_GetCounter(TIM3)+65536*count_temp;
//		 rate=(float)(encoder_cnt-encoder_cnt_pre);
//		 encoder_cnt_pre=encoder_cnt;
//		 motor_speed=72000000/rate;
//		 motor_speed
//	   
// }
//}

void TIM4_IRQHandler(void)
{	
 if(TIM_GetITStatus( TIM4,TIM_IT_Update)!=RESET) 
 {
		 TIM_ClearFlag(TIM4, TIM_IT_Update); 
		 GPIO_WriteBit(GPIOC,GPIO_Pin_13,(BitAction)(1^GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))); 	 
			encoder_cnt=TIM_GetCounter(TIM3)+65536*count_temp;
			if(encoder_cnt > encoder_cnt_pre)
				{
					rate=(float)(encoder_cnt-encoder_cnt_pre);
				}
			else if( encoder_cnt < encoder_cnt_pre )
				{
					rate= 0 - (float)(encoder_cnt-encoder_cnt_pre);
				}
			else {rate=0;}
			motor_speed=(rate*6000)/400;
			frequency=72000000/rate	;
		  encoder_cnt_pre=encoder_cnt;
 }
}

void Direction_Determination (void)
	{		
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)==1)
		{
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==0)
			{CCW=TRUE;}
			else
			{CCW=FALSE;}
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
	

