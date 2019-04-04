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

/*-------------------------------------------------------------------------------
																				ENCODER
--------------------------------------------------------------------------------*/
uint16_t Pulse_value;
uint32_t encoder_cnt, encoder_cnt_pre, rate;
extern volatile uint32_t timer3_cnt_ovr;
/*-------------------------------------------------------------------------------
																				PID
--------------------------------------------------------------------------------*/

double Kp=0.01, Kd=0, Ki=0; // for speed control
double pPart=0, dPart=0, iPart=0; // PID gains
int32_t actual_speed, desired_speed=0, control_speed, desired_speed_1=0;
uint32_t Error, pre_Error;

#define inv_sampling_time 	100											// 1/sampling_time
#define sampling_time       10/1000											// 10ms		
#define PWM_Period					15000


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
		//USARTx_SendChar(USART1,actual_speed);
		encoder_cnt_pre=encoder_cnt;	
}


void Motor_Speed_PID(uint16_t control_speed)
{	  	
	desired_speed=control_speed;
	Error=desired_speed-actual_speed;
	desired_speed_1=Kp*Error+desired_speed_1;	
	if(desired_speed_1>0 && desired_speed_1<15000)
	{
		PWM_update(desired_speed_1);
		
	}
	if(desired_speed_1>=15000)	desired_speed_1=15000-1;
	if(desired_speed_1<=0)			desired_speed_1=0;		
}
