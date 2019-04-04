/**
  ******************************************************************************
  * @file    ADC/3ADCs_DMA/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
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
#include "stm32f10x.h"
#include "stm32f10x_type.h"
#include "delay.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t ADC2ConvertedValue;
extern volatile uint16_t count_temp2, count_temp3;
extern float encoder_pulse1, encoder_pulse2;
extern float count_recent1, count_recent2;
extern float count_update1, count_update2;
extern float motor_speed1, motor_speed2;
/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/
 
/**
  * @brief  This function handles ADC1 and ADC2 global interrupts requests.
  * @param  None
  * @retval None
  */
void ADC1_2_IRQHandler(void)
{
  /* Get injected channel13 converted value */
//  ADC2ConvertedValue = ADC_GetConversionValue(ADC2);
}


/**
  * Timer2, 3 for Encoder Counting Configuration
  */ 
void TIM2_IRQHandler(void)
 {
		uint16_t timer_temp2;
	 if(TIM_GetFlagStatus(TIM2, TIM_FLAG_Update)==SET)
		{
			TIM_ClearFlag(TIM2, TIM_FLAG_Update);
			timer_temp2= TIM2->CNT;									// Counter activation
			if (timer_temp2==65535)	count_temp2--;
			if (timer_temp2==0)			count_temp2++;
		}
 }


 void TIM3_IRQHandler(void)
 {
		uint16_t timer_temp3;
	 if(TIM_GetFlagStatus(TIM3, TIM_FLAG_Update)==SET)
		{
			TIM_ClearFlag(TIM3, TIM_FLAG_Update);
			timer_temp3= TIM3->CNT;									// Counter activation
			if (timer_temp3==65535)	count_temp3--;
			if (timer_temp3==0)			count_temp3++;
		}
			
 }
 
 /**
  * Timer4 for Speed Calculating afet 10ms
		RotationSpeed = (EncoderValue_Last - EncoderValue_Previous) / 2000 ppr) * Freq [Hz]
  */ 
 void TIM4_IRQHandler(void)
	 {
		 if(TIM_GetFlagStatus(TIM3, TIM_FLAG_Update)==SET)
			 {
				 TIM_ClearFlag(TIM4, TIM_FLAG_Update);
				 encoder_pulse1= TIM_GetCounter(TIM2)+65536*count_temp2;
				 encoder_pulse2= TIM_GetCounter(TIM3)+65536*count_temp3;
				 count_recent1=encoder_pulse1;
				 count_recent2=encoder_pulse2;
				 // calcuate motor 1 speed
				 if(count_recent1>count_update1)
					 {
						 motor_speed1=(float)(count_recent1-count_update1)*6000/400;	// ngat 10ms, encoder 400 xung/vong					 
						}
					 else if(count_recent1<count_update1)
						 {
							 motor_speed1=0-(float)(count_recent1-count_update1)*6000/400;	// ngat 10ms, encoder 400 xung/vong			
						 }
						 else {motor_speed1=0;}
					// calcuate motor 2speed
					if(count_recent2>count_update2)
					 {
						 motor_speed1=(float)(count_recent2-count_update2)*6000/400;	// ngat 10ms, encoder 400 xung/vong					 
						}
					 else if(count_recent2<count_update2)
						 {
							 motor_speed1=0-(float)(count_recent2-count_update2)*6000/400;	// ngat 10ms, encoder 400 xung/vong			
						 }
						 else {motor_speed2=0;}	 
						 /*update count 1 and count 2*/
						 count_update1=count_recent1;
						 count_update2=count_recent2;
				}
		}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
