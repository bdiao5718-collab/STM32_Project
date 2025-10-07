#include "led.h"
void Led_Init(void)
{
	/******* 库函数写法**************/
	GPIO_InitTypeDef  GPIO_InitStruct;
	//打开时钟GPIOA组
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//引脚初始化
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
//	RCC->APB2ENR |=(1<<2); 	//打开PA时钟
//	GPIOA->CRH &=~(0xf<<0); //清零
//	GPIOA->CRH |=(2<<0);	//输出模式，最大速度2MHz
//	GPIOA->CRH &=~(3<<2);	//通用推挽输出模式
//	GPIOA->ODR |=~(1<<8);	//默认灭
	
	
}