#ifndef _PID_CONTROL_H
#define _PID_CONTROL_H

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

void Encoder_Reading(void);
void Motor_Speed_PID(uint16_t control_speed);

#endif