#include "Beep.h"

/**************************************
引脚说明:

蜂鸣器连接在PA8
PA8输出在高电平（1），蜂鸣器响；
PA8输出在低电平（0），蜂鸣器不响；
**************************************/
void BEEP_Init(void)
{
	//库函数写法
	//时钟初始化
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;  //通用输出模式
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP; //输出推挽
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;      //引脚5
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;   //上拉输出
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_25MHz; //时钟频率25MHz
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
/*	寄存器写法
//使能GPIOA组时钟
  RCC_AHB1ENR |=(0x01<<0);
	
//设置为输出模式	
	GPIOA_MODER &= ~(0x01<<11);//11位清0
	GPIOA_MODER |= (0x01<<10);//10位置1
	
//输出推挽
	GPIOA_OTYPER &= ~(0x01<<5);//5位清0
	
//设置速度：50MHz
    GPIOA_OSPEEDR |= (0x01<<11);//11位置1	
	GPIOA_OSPEEDR &= ~(0x01<<10);//10位清0
	
	
//设置上拉	
	GPIOA_PUPDR &= ~(0x01<<11);//11位清0
	GPIOA_PUPDR |= (0x01<<10);//10位置1
*/	
	
}