#ifndef _DELAY_H
#define _DELAY_H


//函数声明和宏定义
#include "stm32f10x.h"                  // Device header
#include "stdint.h"
void Delay_Us(u32 runtime);
void Delay_Ms(u32 runtime);
void __NOP(void);  

#endif