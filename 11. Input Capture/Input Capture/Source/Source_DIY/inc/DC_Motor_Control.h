#ifndef _DC_Motor_Control_H
#define _DC_Motor_Control_H

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "DC_Motor_Control.h"

void PWM_Configuration(uint16_t pulse);
void Go_Straight (void);
void Stop_Motor(void);
#endif