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
			Motor_Speed_PID();
 }
}

/*------------------------------PID----------------------------------------------------------*/
//volatile long int Kp=2, Kd=1, Ki=1; // for speed control
//volatile long int pPart=0, iPart=0, dPart=0; // PID gains
//volatile long int Output;
//volatile long int Err, pre_Err;
//uint16_t desired_pulse;

//#define inv_sampling_time 	100											// 1/sampling_time
//#define sampling_time       10											// 10ms									
/*---------------------------------------------------------------------------------------*/
volatile double E=0, E1=0, E2=0;
volatile double  Output=0, LastOutput=0;
volatile double T=0.01; // thoi gian lay mau 10ms
//thanh phan PID
volatile double Kp=5; 
volatile double	Ki=0.03;
volatile double Kd=0.0; 
volatile double alpha, beta, gamma;
	
void Motor_Speed_PID(void)
{
		E=desired_speed-actual_speed;                // error calculating
	
     // PID parts
//    pPart=Kp*Err;
//    dPart=Kd*(Err-pre_Err)*inv_sampling_time;       
//    iPart+=Ki*Err*sampling_time/1000;                  // transform ms into s

//    Output+=pPart+dPart+iPart;
//    pre_Err=Err;
	
			alpha=2*T*Kp + Ki*T*T + 2*Kd;
			beta = T*T*Ki - 4*Kd - 2*T*Kp;
			gamma=2*Kd;
			Output=(alpha*E + beta*E1 + gamma*E2 +2*T*LastOutput)/(2*T);
			LastOutput=Output;
			E2=E1;
			E1=E;
    
//    if(Output>100)
//    {
//      Output=100;
//    }
//		
//		 
//    if(Output<0)
//    {
//      Output=0;
//    }
//			 
//    if(Output>0)
//    {
//      Run_Motor(Output);
//    }
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
	

