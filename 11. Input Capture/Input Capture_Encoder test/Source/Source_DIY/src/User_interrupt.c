//#include "User_interrupt.h"
//#include "stm32f10x.h"
//#include "stm32f10x_it.h"
//#include "delay.h"
//#include "User_interrupt.h"
//#include "Usart_serial.h"
//#include "GPIO_Configuration.h"
//#include "stm32f10x_type.h"
//#include <stdio.h>

//bool CCW=FALSE;

//extern uint32_t  NumberPulse;
//extern uint32_t  Counter_pulse;
//extern uint16_t  CurrentValue;
//extern uint16_t  LastValue;
//extern uint16_t Pre_pulse;
//extern uint16_t Pulse;
//extern uint16_t encoderSpeed;
//extern uint16_t Pulse_value;
//extern unsigned short T;
//extern unsigned long f;

//void TIM1_CC_IRQHandler(void)																						// TIM1 Capture Compare Interrupt
//{
//		if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)											//*Check if the TIM1 Capture Compare 1 interrupt has occured or not*/
//		{
//				TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
//			  CurrentValue  =  TIM_GetCapture1(TIM1);
//				Counter_pulse =  NumberPulse+CurrentValue-LastValue;
//				T=CurrentValue-LastValue;
//				NumberPulse   =  0;
//			  LastValue     =  CurrentValue;
//				f=10000/T		;
//				
//    }
//}

//__IO uint16_t IC1ReadValue1 = 0, IC1ReadValue2 = 0;
//__IO uint16_t CaptureNumber = 0;
//__IO uint32_t Capture = 0;
//__IO uint32_t TIM1Freq;

//void TIM1_CC_IRQHandler(void)
//{ 
//  if(TIM_GetITStatus(TIM1, TIM_IT_CC1) == SET) 
//  {
//    /* Clear TIM3 Capture compare interrupt pending bit */
//    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
//    if(CaptureNumber == 0)
//    {
//      /* Get the Input Capture value */
//      IC1ReadValue1 = TIM_GetCapture1(TIM1);
//      CaptureNumber = 1;
//    }
//    else if(CaptureNumber == 1)
//    {
//      /* Get the Input Capture value */
//      IC1ReadValue2 = TIM_GetCapture1(TIM1); 
//      
//      /* Capture computation */
//      if (IC1ReadValue2 > IC1ReadValue1)
//      {
//        Capture = (IC1ReadValue2 - IC1ReadValue1); 
//      }
//      else
//      {
//        Capture = ((0xFFFF - IC1ReadValue1) + IC1ReadValue2); 
//      }
//      /* Frequency computation */ 
//     // TIM1Freq = (uint32_t) SystemCoreClock / Capture;
//				TIM1Freq = (uint32_t) 10000 / Capture;
//      CaptureNumber = 0;
//    }
//  }
//}

//void TIM1_UP_IRQHandler(void)																						// TIM1 UP Interrupt
//{

//	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
//		{
//				TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
//			  NumberPulse+=0xffff;
//    }
//}

// calculate the feedback speed back every 10ms
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
//}

//void Direction_Determination (void)
//	{
//			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)==1)
//		{
//			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==0)
//			{CCW=FALSE;}
//			else
//			{CCW=TRUE;}
//		}
//	else
//		{
//			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==0)
//				{CCW=TRUE;}
//			else
//				{CCW=FALSE;}
//		}
//		// Determine direction
//		if(CCW==TRUE){
//   // counter_pulse--; 
//  }
//  else{
//   // counter_pulse++;   
//  }
//	}