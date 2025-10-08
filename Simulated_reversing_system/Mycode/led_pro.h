#ifndef _LED_H
#define _LED_H
 
#include "stm32f4xx.h"

#define LED2(a) a?GPIO_ResetBits(GPIOA,GPIO_Pin_6):GPIO_SetBits(GPIOA,GPIO_Pin_6)
#define LED3(a) a?GPIO_ResetBits(GPIOA,GPIO_Pin_7):GPIO_SetBits(GPIOA,GPIO_Pin_7)



void Led_Init(void);


#endif