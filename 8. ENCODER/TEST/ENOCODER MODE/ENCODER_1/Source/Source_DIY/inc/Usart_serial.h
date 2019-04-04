#ifndef _USART_SERIAL_H
#define _USART_SERIAL_H

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"

void GPIO_USART_Configuration(void);
void USARTx_Configuration(USART_TypeDef* USARTx);

/*---------------------------------------Ham truyen ---------------------------------------------------*/
void USARTx_SendChar(USART_TypeDef* USARTx, uint8_t Data);
void USARTx_SendString(USART_TypeDef* USARTx, uint8_t *Str);

/*---------------------------------------Ham nhan ---------------------------------------------------*/
uint8_t USARTx_GetChar(USART_TypeDef* USARTx);
#endif