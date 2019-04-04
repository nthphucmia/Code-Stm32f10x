//#include "stm32f10x.h"
//#include "stm32f10x_it.h"
//#include "delay.h"
//#include "GPIO_Configuration.h"

//extern GPIO_InitTypeDef  	GPIO_InitStructure;

// void Motor_pin_Configuration (void)
// {	 
//	 /* Pin Direction Configuration
//		PA0: IN1
//		PA1: IN2
//		*/
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
//		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//		GPIO_Init(GPIOA, &GPIO_InitStructure);
//			 
//		/* 
//		PA2: ENABLE PIN
//		Pin PWM Configuration
//	 */
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		
//		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;	
//		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
//		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
//		GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//		//test pin PB7	
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
//		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//		GPIO_Init(GPIOB, &GPIO_InitStructure);
//		
//		//test pin PC13
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
//		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
//		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//		GPIO_Init(GPIOC, &GPIO_InitStructure);
// }

// void Encoder_pin_Configuraton (void)
//	 {
//		 //_________________________________INPUT___________________________________________
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9;						// PA8: TIM1_CH1, PA9: TIM1_CH2
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//		GPIO_Init(GPIOA, &GPIO_InitStructure);	 
//		
//		}
//	 
//void GPIO_USART_Configuration(void)
//{	
//	GPIO_InitTypeDef  GPIO_InitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 			//AFIO: Alternate function I/O
//	
///********************************* PORTA - USART1 *************************************/
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	
/////*________________________________ OUTPUT - TX___________________________________*/
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
////	GPIO_Init(GPIOA, &GPIO_InitStructure);  
////	
/////*________________________________ INPUT - RX___________________________________*/
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
////	GPIO_Init(GPIOA, &GPIO_InitStructure);  
////	
///********************************* PORTA - USART2*************************************/
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	
///*________________________________ OUTPUT - TX___________________________________*/
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);  
//	
///*________________________________ INPUT - RX___________________________________*/
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);  
//	
////	/********************************* PORTB - USART3*************************************/
////	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
////	
/////*________________________________ OUTPUT - TX___________________________________*/
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
////	GPIO_Init(GPIOA, &GPIO_InitStructure);  
////	
/////*________________________________ INPUT - RX___________________________________*/
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
////	GPIO_Init(GPIOA, &GPIO_InitStructure);  
//}

//void Test_BlinkingLed(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
//{
//	delay_ms(50);
//	GPIO_WriteBit(GPIOx, GPIO_Pin,(BitAction)(1^GPIO_ReadInputDataBit(GPIOx, GPIO_Pin)));
//	delay_ms(50);
//}
