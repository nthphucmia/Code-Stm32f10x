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

extern volatile uint16_t Pulse_value;
extern volatile uint16_t encoder_cnt, encoder_cnt_pre;
//extern volatile uint16_t rate, actual_speed;

char str[50]; 

volatile uint16_t timer1_temp=0;
volatile uint16_t count_temp=0;

/*------------------------------PID----------------------------------------------------------*/
volatile double Kp=0.01, Kd=0, Ki=0; // for speed control
volatile double pPart=0, dPart=0, iPart=0; // PID gains
volatile double Vc, Vc1;
volatile double Error, Error_1, Error_2;
volatile double u, u_1, PID_speed;
volatile uint16_t rate, actual_speed, desired_speed, control_speed;
volatile double PWM_value;
uint16_t encoderSpeed;
uint16_t desired_pulse, integration_sum;

#define inv_sampling_time 	100											// 1/sampling_time
#define sampling_time       10/1000											// 10ms		
#define PWM_Period					8000

void Motor_Speed_PID(uint16_t control_speed);
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
		 encoder_cnt=TIM_GetCounter(TIM3)+65536*count_temp;	
	 	 Motor_Speed_PID(900);
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
	// thanh phan PID
	control_speed=Kp*Error+desired_speed;
	desired_speed=control_speed;

  PWM_value=(59/10)*desired_speed;
		
	//Run_Motor(3000);	
			
	if(PWM_value>0 && PWM_value<8000)
	{
		Run_Motor(PWM_value);
	}

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
	
