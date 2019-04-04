#ifndef _DC_Motor_Control_H
#define _DC_Motor_Control_H

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "DC_Motor_Control.h"

void PWM_Configuration(uint16_t pulse);
void Motor_control (uint16_t desired_speed);
void Go_Straight (uint16_t pulse);
void Stop_Motor(void);

#endif