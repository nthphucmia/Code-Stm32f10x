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

/*----------------------------------------------------------------------------------------*/
volatile long int Kp=2, Kd=1, Ki=1; // for speed control
volatile long int pPart=0, iPart=0, dPart=0; // PID gains
volatile long int PID_speed;
volatile long int counter_pulse=0;
volatile long time0=0;
volatile long timeF=0;
float time_interval;
float pulse_value;

#define inv_sampling_time 	100											// 1/sampling_time
#define sampling_time       10											// 10ms									


extern volatile uint32_t actual_speed, desired_speed;
extern volatile long int Err, pre_Err;

void Motor_Speed_PID(void)
{
		
	Err=desired_speed-actual_speed;                // error calculating
	
     // PID parts
    pPart=Kp*Err;
    dPart=Kd*(Err-pre_Err)*inv_sampling_time;       
    iPart+=Ki*Err*sampling_time/1000;               // transform ms into s

    PID_speed+=pPart+dPart+iPart;
    pre_Err=Err;
    
    if(PID_speed>0)
    {
      //Motor_control(PID_speed);
    }
}