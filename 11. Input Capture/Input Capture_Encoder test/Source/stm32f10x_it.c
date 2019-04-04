/**
  ******************************************************************************
  * @file    TIM/InputCapture/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

//__IO uint16_t IC3ReadValue1 = 0, IC3ReadValue2 = 0;
//__IO uint16_t CaptureNumber = 0;
//__IO uint32_t Capture = 0;
//__IO uint32_t TIM3Freq;

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

void DebugMon_Handler(void)
{}

void SVC_Handler(void)
{}


void PendSV_Handler(void)
{}


void SysTick_Handler(void)
{}

//void TIM3_IRQHandler(void)
//{ 
//  if(TIM_GetITStatus(TIM3, TIM_IT_CC2) == SET) 
//  {
//    /* Clear TIM3 Capture compare interrupt pending bit */
//    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
//    if(CaptureNumber == 0)
//    {
//      /* Get the Input Capture value */
//      IC3ReadValue1 = TIM_GetCapture2(TIM3);
//      CaptureNumber = 1;
//    }
//    else if(CaptureNumber == 1)
//    {
//      /* Get the Input Capture value */
//      IC3ReadValue2 = TIM_GetCapture2(TIM3); 
//      
//      /* Capture computation */
//      if (IC3ReadValue2 > IC3ReadValue1)
//      {
//        Capture = (IC3ReadValue2 - IC3ReadValue1); 
//      }
//      else
//      {
//        Capture = ((0xFFFF - IC3ReadValue1) + IC3ReadValue2); 
//      }
//      /* Frequency computation */ 
//      TIM3Freq = (uint32_t) SystemCoreClock / Capture;
//      CaptureNumber = 0;
//    }
//  }
//}

unsigned short icValue=0;
unsigned short count=0;
unsigned short preValue=0;
unsigned short T=0;
unsigned long f=0;

void TIM1_CC_IRQHandler(void)																						// TIM1 UP Interrupt
{
	/*Check if the TIM1 Capture Compare 1 interrupt has occured or not*/
				if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)									
		{
				TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
				//count=count+1;
				icValue  =  TIM_GetCapture1(TIM1);				
				T=icValue-preValue;
				preValue=icValue;
				f=10000/T		;								// f=clock_frequency/T (clock frequency=72000000/7200 (prescaler=7200)
    }
}
