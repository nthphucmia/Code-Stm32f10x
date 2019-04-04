#include "User_interrupt.h"
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"
#include "User_interrupt.h"
#include "Usart_serial.h"
#include "GPIO_Configuration.h"
#include "stm32f10x_type.h"
#include "stdio.h"
#include "PID_control.h"
		
extern volatile uint16_t encoderSpeed;
extern volatile uint16_t Pulse, pre_Pulse;
extern volatile uint16_t encoder_cnt, encoder_cnt_pre, rate;
extern volatile uint32_t actual_speed, desired_speed;
extern volatile long int Err, pre_Err;

char str[50]; 
bool CCW=FALSE;	
uint16_t timer1_temp=0;
uint16_t count_temp=0;

/*------------------------------PID----------------------------------------------------------*/
volatile double Kp=3, Kd=0, Ki=0; // for speed control
volatile double pPart=0, iPart=0, dPart=0; // PID gains
volatile int PID_speed, pre_Out, Output;

#define inv_sampling_time 	100											// 1/sampling_time
#define sampling_time       10											// 10ms									


extern volatile uint32_t actual_speed, desired_speed;
extern volatile long int Err, pre_Err, pre_pre_Err;
extern volatile uint16_t desired_pulse;

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
			if(encoder_cnt > encoder_cnt_pre)
				{
					rate=(float)(encoder_cnt-encoder_cnt_pre);
				}
			else if( encoder_cnt < encoder_cnt_pre )
				{
					rate= 0 - (float)(encoder_cnt-encoder_cnt_pre);
				}
			else {rate=0;}
			actual_speed=(rate*6000)/374;
		  encoder_cnt_pre=encoder_cnt;
			
			// PID activation
			PID_speed=Motor_Speed_PID(11);
			Run_Motor(PID_speed);
 }
}

uint32_t Motor_Speed_PID(uint16_t set_pulse)
{
	desired_pulse=set_pulse;	
	Err=desired_pulse-rate;                // error calculating
	
     // PID parts
    pPart=Kp*Err;
    dPart=Kd*(Err-pre_Err)*inv_sampling_time;       
    iPart+=Ki*Err*sampling_time/1000;                  // transform ms into s

    Output+=pPart+dPart+iPart;
    
//	  pPart=Kp*(Err-pre_Err);     
//    dPart = Kd*inv_sampling_time*( Err - 2*pre_Err+ pre_pre_Err);                  // transform ms into s
//		iPart = Ki*0.5*sampling_time*(Err+ pre_Err)/1000;
//    PID_speed+=pPart + iPart + dPart;
//		pre_pre_Err = pre_Err;
//		pre_Err = Err; 
	
//    if(Output>2000)
//    {
//      Output=2000-1;
//    }
//		
//		if(Output<0)
//    {
//      Output=1;
//    }
//		
//		if(Output>0)
//    {
//      Output=Output;
//    }
		pre_Err=Err;
		return(Output);
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
	

