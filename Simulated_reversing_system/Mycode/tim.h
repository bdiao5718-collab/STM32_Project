#ifndef _TIM_H
#define _TIM_H
 
#include "stm32f4xx.h"

extern volatile int auto_re;

void Tim2_IT_Init(uint32_t sec,FunctionalState status);
void Tim2_Init(void);

#endif
