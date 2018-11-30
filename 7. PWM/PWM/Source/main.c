
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef  			GPIO_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
TIM_OCInitTypeDef 			TIM_OCInitStructure;

void GPIO_Configuration(void);
void TimerBase_Configuration(void);
void PWM_Configuration(void);


/* Private functions ---------------------------------------------------------*/

int main(void)
{ 
	GPIO_Configuration();
	TimerBase_Configuration();
	PWM_Configuration();	
  while (1)
  {
	}
}
void GPIO_Configuration(void)
{
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/* Configure PB0 PB1 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			//timer4-channel 4
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// chan I/O vua la ngo ra vua la ngo vao (ko co tro keo len/xuong)
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
}
 
/*Cau hinh chan output cua timerbase*/
/*
-	PWM frequency: 100us (10kHz)
-	Pulse width: gia tri muc cao so voi period
- TIM_Prescaler:
Choose: Prescaler=0
				Timer_tick_frequency=Timer_default_frequence/(Prescaler+1)
	Ex:72000000/(0+1)=72MHz
- TIM_Period:
			TIM_Period=(Timer_tick_frequency/PWM_frequence)-1
	Ex: (72000000/10000)-1=7199	
*/
void TimerBase_Configuration(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=0; 
	TIM_TimeBaseInitStructure.TIM_Period=7200-1;   // 10kHz
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
}

/*
		25% duty cycle: pulse_length=((7199+1)*25)/100-1=1799
		50% duty cycle: pulse_length=((7199+1)*50)/100-1=3599
		75% duty cycle: pulse_length=((7199+1)*75)/100-1=5399
		100% duty cycle: pulse_length=((7199+1)*100)/100-1=7199
*/
void PWM_Configuration(void)
	{				
		/*Cau hinh channel4 o mode PWM, cau hinh output compare su dung cho PWM*/
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				// clear on compare match
		TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;
		
		TIM_OCInitStructure.TIM_Pulse=1799;
		TIM_OC1Init(TIM4, &TIM_OCInitStructure);
		TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

		TIM_OCInitStructure.TIM_Pulse=3599;		//3599
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
		
		TIM_OCInitStructure.TIM_Pulse=5399;
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
		
		TIM_OCInitStructure.TIM_Pulse=7199;
		TIM_OC2Init(TIM4, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

		TIM_ARRPreloadConfig(TIM4, ENABLE); 	
		TIM_Cmd(TIM4, ENABLE);												// Cho phep TIM4 hoat dong
	}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
