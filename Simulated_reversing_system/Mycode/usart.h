#ifndef _USART_H
#define _USART_H
 
#include "stm32f4xx.h"

extern uint8_t data;
extern uint8_t flag;

void Usart1_Init(int myBaudRate);
void BlueTeeth_Usart_Init(int myBaudRate);

#endif