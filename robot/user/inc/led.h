#ifndef _LED_H
#define _LED_H


//函数声明和宏定义
#include "stm32f10x.h"                  // Device header

void Led_Init(void);

#define LED_ON GPIOA->ODR &=~(1<<8)
#define LED_OFF GPIOA->ODR |=(1<<8)


#endif