#include "User_interrupt.h"
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"
#include "User_interrupt.h"
#include "Usart_serial.h"
#include "GPIO_Configuration.h"
#include "stm32f10x_type.h"

bool CCW=FALSE;

extern uint32_t  NumberPulse;
extern uint32_t  Counter_pulse;
extern uint16_t  CurrentValue;
extern uint16_t  LastValue;
				uint16_t Pre_pulse=0;
				uint16_t Pulse=0;
extern	uint16_t encoderSpeed;
extern	uint16_t Pulse_value;

extern volatile short encoder_cnt, encoder_cnt_pre;
extern volatile short rate;

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

//// calculate the feedback speed back every 10ms
//void TIM4_IRQHandler(void)
//{
//				Pre_pulse = Counter_pulse;  
//				if (CCW==TRUE)
//					{
//						 Pulse_value = (float)(Pulse-Pre_pulse);
//					}
//				else
//					{
//						 Pulse_value = (float)-(Pulse-Pre_pulse);
//					}
//        //encoderSpeed=(float)(((pulse_value)/400)/(time_interval)*60000;			// encoder do phan giai 400 xung
//        delay_ms(100);
//        Pulse = Pre_pulse;
//	      Pulse=0; 
//        Counter_pulse=0;
//					
//				// Display debug
//				//USARTx_SendChar(USART2, Counter_pulse);
//				//USARTx_SendString(USART2,"TIM4_IRQHandler\r");
//}

void Direction_Determination (void)
	{
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)==1)
		{
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==0)
			{CCW=FALSE;}
			else
			{CCW=TRUE;}
		}
	else
		{
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==0)
				{CCW=TRUE;}
			else
				{CCW=FALSE;}
		}
	}
	

//void TIM4_IRQHandler(void)
//{	
//if(TIM_GetITStatus( TIM4,TIM_IT_Update)!=RESET) //if update flag turns on
//{
//	 GPIO_WriteBit(GPIOC,GPIO_Pin_13,(BitAction)(1^GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))); 
//	 //USARTx_SendString(USART2,"Test\n\r");
//	 delay_ms(100);
//	 TIM_ClearFlag(TIM4, TIM_FLAG_Update); //clear update flag
//}
//}

void TIM4_IRQHandler(void)
{	
 if(TIM_GetITStatus( TIM4,TIM_IT_Update)!=RESET) //if update flag turns on
 {
		 GPIO_WriteBit(GPIOC,GPIO_Pin_13,(BitAction)(1^GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))); 
     encoder_cnt=TIM_GetCounter(TIM1);
		 rate=(encoder_cnt-encoder_cnt_pre)/400;
		 encoder_cnt_pre=encoder_cnt;
     TIM_ClearFlag(TIM4, TIM_FLAG_Update); //clear update flag
 }
}