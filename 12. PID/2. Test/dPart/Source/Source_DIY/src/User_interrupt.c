#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#include "stdio.h"
#include "Usart_serial.h"
#include "User_interrupt.h"
#include "GPIO_Configuration.h"
#include "Encoder_Configuration.h"
#include "DC_Motor_Control.h"
#include "stm32f10x_type.h"
#include "stdio.h"

bool CCW=FALSE;			
volatile uint16_t Pulse_value;
volatile uint32_t encoder_cnt, encoder_cnt_pre, total_pulse;
char str[50]; 
volatile uint32_t timer3_cnt_ovr=0;
/*------------------------------PID----------------------------------------------------------*/
// for speed control
//volatile double Kp=0.1; 
//volatile double Kp=0.05; 
volatile double Kp=0.05; 
volatile double	Kd=0.01;
volatile double Ki=0; 

volatile double pPart=0, dPart=0, iPart=0; // PID gains
volatile double Vc, Vc1;
volatile double Error, Error_1, Error_2, pre_Error;
volatile double u, u_1, PID_speed;
volatile int32_t rate, actual_speed, desired_speed=0, control_speed, desired_speed_1=0;
volatile int32_t PWM_value;

#define inv_sampling_time 	100											// 1/sampling_time
#define sampling_time       10											// 10ms		
#define PWM_Period					15000

/*---------------------------------------------------------------------------------------*/

void TIM3_IRQHandler(void)																
{	
 if(TIM_GetITStatus( TIM3,TIM_IT_Update)!=RESET) 				// ngat khi tran
		{
			TIM_ClearFlag(TIM3, TIM_IT_Update);
			timer3_cnt_ovr++;		
    }
}

void TIM4_IRQHandler(void)
{	
 if(TIM_GetITStatus( TIM4,TIM_IT_Update)!=RESET) 
 {
		 TIM_ClearFlag(TIM4, TIM_IT_Update);
		 Encoder_Reading();	
		 Motor_Speed_PID(700);
 }
}

void Encoder_Reading(void)
{
	Pulse_value=TIM_GetCounter(TIM3); 
	encoder_cnt=TIM_GetCounter(TIM3)+65536*timer3_cnt_ovr;	
	
		if(encoder_cnt > encoder_cnt_pre)
			{
				rate=(float)(encoder_cnt-encoder_cnt_pre);
			}
		else if( encoder_cnt < encoder_cnt_pre )
			{
				rate= 0 - (float)(encoder_cnt-encoder_cnt_pre);
			}
		else {rate=0;}
		
		actual_speed=(rate*6000)/200;
		encoder_cnt_pre=encoder_cnt;	
}


void Motor_Speed_PID(uint16_t control_speed)
{	  	
	desired_speed=control_speed;
	Error=desired_speed-actual_speed;
	//PID part
	pPart=Kp*Error;
	dPart=Ki*(Error-pre_Error)*inv_sampling_time;
	iPart+=Ki*Error*sampling_time/1000;
	
	desired_speed_1+=pPart;//+dPart;	
	pre_Error=Error;
	//constrain
	if(desired_speed_1>0 && desired_speed_1<PWM_Period)
	{
		Run_Motor(desired_speed_1);
	}
	if(desired_speed_1>=PWM_Period)				desired_speed_1=PWM_Period-1;
	if(desired_speed_1<=0)								desired_speed_1=0;		
}
