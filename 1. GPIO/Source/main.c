/**
  ******************************************************************************
  * @file    ADC/3ADCs_DMA/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
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
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup ADC_3ADCs_DMA
  * @{
  */ 


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ADC_InitTypeDef ADC_InitStructure;
DMA_InitTypeDef DMA_InitStructure;
GPIO_InitTypeDef  GPIO_InitStructure;

void GPIO_Configuration(void);

/* Private functions ---------------------------------------------------------*/

int main(void)
{ 
	GPIO_Configuration();

  while (1)
  {
		/*
		Phep toan XOR "^":
		Giong nhau bang 0 ( A XOR A =0)
		Khac nhau bang  1  (0 XOR A =A)
		*/
		
		GPIO_WriteBit(GPIOB, GPIO_Pin_0,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))); 	// toggle pin_7
		GPIO_WriteBit(GPIOB, GPIO_Pin_1,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)));
		GPIO_WriteBit(GPIOB, GPIO_Pin_2,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2)));
		GPIO_WriteBit(GPIOB, GPIO_Pin_3,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)));
		GPIO_WriteBit(GPIOB, GPIO_Pin_4,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)));
		GPIO_WriteBit(GPIOB, GPIO_Pin_5,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)));
		GPIO_WriteBit(GPIOB, GPIO_Pin_6,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)));
		GPIO_WriteBit(GPIOB, GPIO_Pin_7,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)));
		delay_ms(100);
	}
}
/*
GPIO: General function Input/Output
ALternate function: include I2C, SPI, USART, CCP, PWM, Clock, ADC, etc,...
*/
void GPIO_Configuration(void)
{
		/* MODE INPUT */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;			//BUTTON 4
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);  
		
		/*Mode OUTPUT */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/* Configure PB0 PB1 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_2|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				//LED6	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	/* Push pull: when the output goes low, it is actively "pulled" to ground. 
		 Conversly, when the output is set to high, it is actively "pushed" toward Vcc.*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 				
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
}
 

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{ 
  while (1)
  {
  }
}

#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
