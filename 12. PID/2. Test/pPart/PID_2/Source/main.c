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
#include "stdio.h"
#include "Usart_serial.h"
#include "User_interrupt.h"
#include "GPIO_Configuration.h"
#include "Encoder_Configuration.h"
#include "DC_Motor_Control.h"
#include "stm32f10x_type.h"
#include "stdio.h"
#include "PID_control.h"

/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
NVIC_InitTypeDef 		NVIC_InitStructure;
GPIO_InitTypeDef  	GPIO_InitStructure;
EXTI_InitTypeDef  	EXTI_InitStructure;
TIM_OCInitTypeDef 	TIM_OCInitStructure;
TIM_ICInitTypeDef 	TIM_ICInitStructure;
TIM_ICInitTypeDef 	TIM_ICInitStructure;

/*----------------------------------------------------------------------------------------*/
volatile uint16_t encoderSpeed;
volatile uint16_t Pulse, pre_Pulse;;
volatile uint16_t encoder_cnt, encoder_cnt_pre, rate;
volatile uint32_t actual_speed, desired_speed;
volatile long int Err, pre_Err, pre_pre_Err;
volatile uint16_t desired_pulse, actual_pulse;

int main(void)
{ 
//	GPIO_USART_Configuration();
//	USARTx_Configuration(USART2);
	
	Motor_pin_Configuration();
	Encoder_pin_Configuraton();
	
	//Activate motor
	//Motor_control(50);
	//Run_Motor(500);
  //Stop_Motor_no_BRA();
	
	//Encoder Activating
	Encoder_System_Configuration();
	Encoder_Reading_Configuration();
  NVIC_Configuration();
	
	
	while (1)
  {	
		
	}
}

	
/***********************************************************************/	