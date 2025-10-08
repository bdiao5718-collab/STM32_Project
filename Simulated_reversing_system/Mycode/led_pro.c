#include "led_pro.h"

/******************************

引脚说明：
LED2（D2）连接在PA6
PA6输出在低电平（0），灯亮；PA6输出在高电平（1），灯灭；
LED3（D3）连接在PA7
PA7输出在低电平（0），灯亮；PA7输出在高电平（1），灯灭；

*******************************/
void Led_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;             //引脚
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;         //输出模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;        //输出推挽
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;     //设置25MHz
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;          //设置上拉
	
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
    GPIO_Init(GPIOA,&GPIO_InitStruct);

 

}
