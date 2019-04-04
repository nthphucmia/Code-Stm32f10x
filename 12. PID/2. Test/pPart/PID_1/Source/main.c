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

/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
NVIC_InitTypeDef 		NVIC_InitStructure;
GPIO_InitTypeDef  	GPIO_InitStructure;
EXTI_InitTypeDef  	EXTI_InitStructure;
TIM_OCInitTypeDef 	TIM_OCInitStructure;
TIM_ICInitTypeDef 	TIM_ICInitStructure;
TIM_ICInitTypeDef 	TIM_ICInitStructure;


/*----------------------------------------------------------------------------------------*/
volatile long int Kp=8, Kd=10, Ki=1; // for speed control
volatile long int pPart=0, iPart=0, dPart=0; // PID gains
volatile long int Output;
volatile long int Err, pre_Err;
volatile long int counter_pulse=0;
volatile long time0=0;
volatile long timeF=0;
float time_interval;
//uint16_t Pre_pulse=0;
//uint16_t Pulse=0;
float pulse_value;
float encoderSpeed = 0;
double rSpeed;
double rpm_default;
/*----------------------------------------------------------------------------------------*/

uint32_t encoder_cnt_pulse, encoder_cnt_pulse_pre;
uint32_t rate, actual_speed, desired_speed;

//#define inv_sampling_time 	1/sampling_time
//#define sampling_time       8000

void Motor_Speed_PID(void);
	
int main(void)
{ 
//	GPIO_USART_Configuration();
//	USARTx_Configuration(USART2);
	
	Motor_pin_Configuration();
	Encoder_pin_Configuraton();
	
	//Activate motor
	 Go_Straight(9);
	
	//Active the encoder	
	Encoder_System_Configuration();
	Encoder_Reading_Configuration();
	NVIC_Configuration();
	

	while (1)
  {	
	}
}

//void Motor_Speed_PID(void)
//{
//		Err=(desired_speed-actual_speed);                // error calculating
//     // PID parts
//    pPart=Kp*Err;
//    dPart=Kd*(Err-pre_Err)*inv_sampling_time;       
//    iPart+=Ki*Err*sampling_time/1000;               // transform ms into s

//    Output+=pPart+dPart+iPart;
//    pre_Err=Err;
//    
//    if(Output>0)
//    {
//      Motor_control(Output);
//    }
//}
/***********************************************************************/	