//#include "stm32f10x.h"
//#include "stm32f10x_it.h"
//#include "Encoder_Configuration.h"
//#include "stm32f10x_type.h"
//#include "Usart_serial.h"

//extern TIM_TimeBaseInitTypeDef 	TIM_TimeBaseInitStructure;
//extern NVIC_InitTypeDef 				NVIC_InitStructure;
//extern GPIO_InitTypeDef  				GPIO_InitStructure;
//extern EXTI_InitTypeDef  				EXTI_InitStructure;
//extern TIM_OCInitTypeDef 				TIM_OCInitStructure;
//extern TIM_ICInitTypeDef 				TIM_ICInitStructure;

//extern uint32_t  NumberPulse;
//extern uint32_t  Frequency;
//extern uint16_t  CurrentValue;
//extern uint16_t  LastValue;


//void Encoder_system_Configuration(void)
//{
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

//	/*----------------------------Timer1 base configuration-------------------------------------*/
//	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;				
//	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
//	TIM_TimeBaseInitStructure.TIM_Period=0xffff;
//	TIM_TimeBaseInitStructure.TIM_Prescaler=1;
//	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;	
//	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

//	/*-----------------Encoder 1 configuration - Input Capture Interface-----------------------*/
//	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;							// PA8: TIM1_CH1
//	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
//	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
//	TIM_ICInitStructure.TIM_ICFilter=0x0f;
//	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
//	TIM_ICInit(TIM1, &TIM_ICInitStructure);
//	
//	/*Configures the TIM1 Encoder Interface*/
//	TIM_EncoderInterfaceConfig(TIM1,TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
//	
//	/*Enable Timer1 */
//	TIM_Cmd(TIM1, ENABLE);
//	
//	TIM_ClearFlag(TIM1, TIM_FLAG_Update); 			// clear update flag
//	TIM_ITConfig(TIM1,TIM_IT_CC1,ENABLE);
//	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
//}

//	void NVIC_Configuration(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;

//  /* Enable the TIM1 global Interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);

////	//Cau hinh cho nhom Uu Tien NVIC
////  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
////	//Chon kenh ngat
////  NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
////  //Chon Preemption	
////  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
////	//Chon hinh Sub
////  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
////	//Enable kenh NVIC
////  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
////  NVIC_Init(&NVIC_InitStructure); 
////	
////  //Cau hinh cho nhom Uu Tien NVIC
////  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
////	//Chon kenh ngat
////  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
////  //Chon Preemption	
////  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
////	//Chon hinh Sub
////  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
////	//Enable kenh NVIC
////  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
////  NVIC_Init(&NVIC_InitStructure);  	
//}

///* TIM4 is interrupted every 10ms to calculate the velocity.*/
//void Encoder_reading_configuration (void)
//	{
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//		
//		// TIM4 Configuration
//		TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
//		TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
//		TIM_TimeBaseInitStructure.TIM_Period=100-1;
//		TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;
//		TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
//		
//		TIM_ClearFlag(TIM4, TIM_FLAG_Update); 			// clear update flag
//		TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);  // enable Update interrupt 
//		TIM_Cmd(TIM4, ENABLE); 											// enable timer 4
//		
//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//		// Enable the TIM4 global interrupt
//		NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
//		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//		NVIC_Init(&NVIC_InitStructure);	
//	}
//	

