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

bool CCW=FALSE;			
uint16_t encoderSpeed;
uint16_t Pulse_value;
uint16_t encoder_cnt, encoder_cnt_pre;
extern uint16_t rate, actual_speed, desired_speed;
char str[50]; 

uint16_t timer1_temp=0;
uint16_t count_temp=0;

/*------------------------------PID----------------------------------------------------------*/
volatile double Kp=2.1, Kd=0.04, Ki=0.02; // for speed control
volatile double a=0, b=0, c=0; // PID gains
volatile double Error, Error_1, Error_2;
//volatile uint32_t u, u_1, u_2, PID_speed;
volatile double u, u_1, u_2, PID_speed;

uint16_t desired_pulse, integration_sum;

#define inv_sampling_time 	100											// 1/sampling_time
#define sampling_time       10/1000											// 10ms									
/*---------------------------------------------------------------------------------------*/

void TIM3_IRQHandler(void)																
{
		if (TIM_GetFlagStatus(TIM3, TIM_FLAG_Update) == SET)
		{
			TIM_ClearFlag(TIM3, TIM_FLAG_Update);
			timer1_temp = TIM3->CNT;	
			if (timer1_temp == 65535) count_temp--	;
			if (timer1_temp == 0)			count_temp++	;
    }
}


void TIM4_IRQHandler(void)
{	
 if(TIM_GetITStatus( TIM4,TIM_IT_Update)!=RESET) 
 {
		 TIM_ClearFlag(TIM4, TIM_IT_Update); 
		 GPIO_WriteBit(GPIOC,GPIO_Pin_13,(BitAction)(1^GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))); 	 
			encoder_cnt=TIM_GetCounter(TIM3)+65536*count_temp;
			Motor_Speed_PID(510);
 }
}

void Motor_Speed_PID(uint16_t control_speed)
{
		desired_speed=control_speed;
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
		
		Error=desired_speed-actual_speed;               
		a = (Kp + Ki * sampling_time/2 + Kd*inv_sampling_time);
		b = (-Kp + Ki * sampling_time/2 - 2*Kd*inv_sampling_time);
		c = Kd*inv_sampling_time;
	
		u = u_1 + a*Error + b*Error_1 + c*Error_2;
	
		u_1 = u;
		Error_1 = Error;
		Error_2 = Error_1;
	
//		if (u<=0)
//		{
//			u=0;
//		}
		
		if(u>0 && u<100)
		{
			u=u*80;
		}
			
//		if(u>=100)
//		{
//			u=8000-1;		
//		}
		
		Run_Motor(u);
}

void Direction_Determination (void)
	{		
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)==1)
		{
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==0)
			{CCW=TRUE;}
			else
			{CCW=FALSE;}
		}
	else
		{
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==0)
				{CCW=FALSE;}
			else
				{CCW=TRUE;}
		}
		
// Direction Test
		if(CCW==TRUE)
			{
			  sprintf(str,"\n\rCCW\n\r");
				USARTx_SendString(USART2,str);
			}
  else
		{
				 sprintf(str,"\n\rCW\n\r");
				USARTx_SendString(USART2,str);
		}
	}
	
