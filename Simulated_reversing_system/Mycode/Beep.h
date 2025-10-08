#ifndef _BEEP_H
#define _BEEP_H

#include "stm32f4xx.h"

#define RCC_AHB1ENR         *((volatile unsigned int *)(0x40023800+0x30))//(0x40023800+0x30)Ϊ��ֵ�����ǵ�ַ;ֵǿ��ת��Ϊ��ַ��ͨ�������ŷ��ʵ�ַ�ռ�

#define GPIOA_MODER         *((volatile unsigned int *)(0x40020000+0x00))//ֵǿ��ת��Ϊ��ַ��ͨ�������ŷ��ʵ�ַ�ռ�
#define GPIOA_OTYPER        *((volatile unsigned int *)(0x40020000+0x04))//ֵǿ��ת��Ϊ��ַ��ͨ�������ŷ��ʵ�ַ�ռ�
#define GPIOA_OSPEEDR       *((volatile unsigned int *)(0x40020000+0x08))//ֵǿ��ת��Ϊ��ַ��ͨ�������ŷ��ʵ�ַ�ռ�
#define GPIOA_PUPDR         *((volatile unsigned int *)(0x40020000+0x0c))//ֵǿ��ת��Ϊ��ַ��ͨ�������ŷ��ʵ�ַ�ռ�
#define GPIOA_ODR           *((volatile unsigned int *)(0x40020000+0x14))//ֵǿ��ת��Ϊ��ַ��ͨ�������ŷ��ʵ�ַ�ռ�



void BEEP_Init(void);


#endif