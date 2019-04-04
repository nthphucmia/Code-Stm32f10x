#include "stm32f10x.h"
#include "Usart_serial.h"
#include "stdio.h"
#include "DC_Motor_Control.h"
#include "GPIO_Configuration.h"
#include "Encoder_Configuration.h"
#include "stm32f10x_type.h"

TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
NVIC_InitTypeDef 				NVIC_InitStructure;
GPIO_InitTypeDef  			GPIO_InitStructure;
EXTI_InitTypeDef  			EXTI_InitStructure;
TIM_OCInitTypeDef 			TIM_OCInitStructure;
TIM_ICInitTypeDef  			TIM_ICInitStructure;

/* Private function prototypes -----------------------------------------------*/
uint16_t  CurrentValue;
uint32_t  NumberPulse;
uint32_t  Frequency;
uint16_t  CurrentValue;
uint16_t  LastValue;
uint32_t  Counter_pulse;

uint16_t  CurrentValue;
uint16_t  LastValue;
uint16_t Pre_pulse=0;
uint16_t Pulse=0;
uint16_t encoderSpeed;
uint16_t Pulse_value;

volatile short encoder_cnt, encoder_cnt_pre=0;
volatile short rate;

void Encoder_pin_Configuraton(void );
void NVIC_Configuration(void);
void Encoder_System_Configuration(void);
void Input_Capture_Test (void);

int main(void)
{

	Encoder_pin_Configuraton();
	NVIC_Configuration();
	Encoder_System_Configuration();
	
  while (1)
		{	
			delay_ms(1000);
			encoder_cnt=TIM_GetCounter(TIM1);
			rate=(encoder_cnt-encoder_cnt_pre)/400;
			encoder_cnt_pre=encoder_cnt;
		}
}

void Encoder_pin_Configuraton (void)
	 {
		    /**TIM1 GPIO Configuration    
    PA8     ------> TIM1_CH1
    PA9     ------> TIM1_CH2 
    */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		 
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9;						
		GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);	 
		
		}
	
	void NVIC_Configuration(void)
{
  /* Enable the TIM1 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void Encoder_System_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	/*----------------------------Timer1 base configuration-------------------------------------*/
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;				
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=0xffff;
	TIM_TimeBaseInitStructure.TIM_Prescaler=0;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

	/*-----------------Encoder 1 configuration - Input Capture Interface-----------------------*/
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;							// PA8: TIM1_CH1, PA9: TIM1_CH2
	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICFilter=0;
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM1, &TIM_ICInitStructure);
	
	/*Configures the TIM1 Encoder Interface*/
	TIM_EncoderInterfaceConfig(TIM1,TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
		
	TIM_SetCounter(TIM1,0);
	
	/*Enable Timer1 */
	TIM_Cmd(TIM1, ENABLE);
	
	// clear update flag
	TIM_ClearFlag(TIM1, TIM_FLAG_Update); 		
	
	/* Enables the TIM1 Capture Compare channel 1 Interrupt source */
	TIM_ITConfig(TIM1,TIM_IT_CC1,ENABLE);
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
}