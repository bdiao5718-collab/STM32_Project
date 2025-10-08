#include "key.h"

/*****************************************************
引脚说明：
KEY0连接在PE4,KEY1连接在PE3
按键未按下，PE4为高电平（1）
按键  按下，PE4为低电平（0）
******************************************************/
void Key_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStruct;
	//时钟初始化
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_3;         //引脚4
 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;      //输入模式
 GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;      //设置上拉
	
 GPIO_Init(GPIOE,&GPIO_InitStruct);
}