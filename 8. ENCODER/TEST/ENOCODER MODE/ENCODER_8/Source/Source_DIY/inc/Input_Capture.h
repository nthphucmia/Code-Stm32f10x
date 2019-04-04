#ifndef _Input_Capture_H
#define _Input_Capture_H

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

void Input_Capture_TIM1_Configuration (void);
void TIM1_CC_IRQHandler(void)		;

#endif