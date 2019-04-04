#ifndef _USER_INTERRUPT_H
#define _USER_INTERRUPT_H

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"

void TIM1_UP_IRQHandler(void);
void TIM1_CC_IRQHandler(void);
void TIM4_IRQHandler(void);
#endif