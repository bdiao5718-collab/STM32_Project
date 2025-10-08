#ifndef _BEEP_H
#define _BEEP_H

#include "stm32f4xx.h"

#define RCC_AHB1ENR         *((volatile unsigned int *)(0x40023800+0x30))//(0x40023800+0x30)为数值，而非地址;值强制转换为地址，通过解引脚访问地址空间

#define GPIOA_MODER         *((volatile unsigned int *)(0x40020000+0x00))//值强制转换为地址，通过解引脚访问地址空间
#define GPIOA_OTYPER        *((volatile unsigned int *)(0x40020000+0x04))//值强制转换为地址，通过解引脚访问地址空间
#define GPIOA_OSPEEDR       *((volatile unsigned int *)(0x40020000+0x08))//值强制转换为地址，通过解引脚访问地址空间
#define GPIOA_PUPDR         *((volatile unsigned int *)(0x40020000+0x0c))//值强制转换为地址，通过解引脚访问地址空间
#define GPIOA_ODR           *((volatile unsigned int *)(0x40020000+0x14))//值强制转换为地址，通过解引脚访问地址空间



void BEEP_Init(void);


#endif