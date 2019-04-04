/********************************************************************************
 1. Use time1 with 4 channels to control 2 motors for PWM are TIM2_CH3 with frequency 2kHz. 
 2. Two encoders combined in motors have 2 phase A,B read by TIM3 with interrupt configuration.
 3. TIM4 is interrupted every 10ms to calculate the velocity.
 4. The calculated velocity is printed in PC by UART with baud rate: 115200
 
 The connected diagram
 STM32F103C8:
 PA2, PA3: Module UART2
 PA6, PA7: phase A, B encoder (motor2) - TIM3				
 PA0, PA1: upper and lower bridge driver motor1		
 PA2: TIM2-CH3
 ----------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"
#include "Usart_serial.h"
#include "User_interrupt.h"
#include "GPIO_Configuration.h"
#include "Encoder_Configuration.h"
#include "DC_Motor_Control.h"

/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
NVIC_InitTypeDef 		NVIC_InitStructure;
GPIO_InitTypeDef  	GPIO_InitStructure;
EXTI_InitTypeDef  	EXTI_InitStructure;
TIM_OCInitTypeDef 	TIM_OCInitStructure;
TIM_ICInitTypeDef 	TIM_ICInitStructure;
TIM_ICInitTypeDef 	TIM_ICInitStructure;

/*----------------------------------------------------------------------------------------*/
uint32_t  NumberPulse;
uint32_t  Counter_pulse;
uint16_t  CurrentValue;
uint16_t  LastValue;
uint16_t encoderSpeed;
uint16_t Pulse_value;
/*----------------------------------------------------------------------------------------*/

int main(void)
{ 		
	Motor_pin_Configuration();
	Encoder_pin_Configuraton();
	Encoder_system_Configuration();
	
	// Debug encoder reading
	GPIO_USART_Configuration();
	USARTx_Configuration(USART2);
	
	while (1)
  {
		Test_BlinkingLed(GPIOB, GPIO_Pin_7);
		// run motor
		//Go_Straight ();
		delay_ms(100);
		// reading encoder
		USARTx_SendString(USART2,"Encoder reading Test");
		Encoder_reading_configuration();
		//USARTx_SendString(USART2,"Encoder reading Test");
		USARTx_SendChar(USART2, Pulse_value);
		
	  delay_ms(1000);
	}
}
 
/***********************************************************************/	