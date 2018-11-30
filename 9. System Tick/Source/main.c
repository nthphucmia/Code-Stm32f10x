/**
  ******************************************************************************
  System Tick:
	Can thoi gian chinh xac gan nhu tuyet doi, thoi gian delay ngan (us), code da
	su dung nhieu ngat thi nen dung System Tick. 
	Ban chat System Tick la dung ngat de dem va ngat System Tick co thu tu uu tien
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
GPIO_InitTypeDef  GPIO_InitStructure;

void SysTick_Configuration(void);
void Delay_ms_systick(uint16_t time);

/* Private functions ---------------------------------------------------------*/

int main(void)
{ 
	SysTick_Configuration();
	
  while (1)
  {
		
	}
}

void SysTick_Configuration(void)
{
	/* Setup SysTick Timer for 1 ms interrupts */
  if (SysTick_Config(SystemCoreClock / 1000)) //1000000:us 1000:ms 100000:us
  { 
  /* Capture error */
  Delay_ms_systick(500)		;
	}
}

void Delay_ms_systick(uint16_t time)
{
	uint16_t TimmingDelay=time;
	while(TimmingDelay!=0);
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{ 
  while (1)
  {
  }
}

#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
