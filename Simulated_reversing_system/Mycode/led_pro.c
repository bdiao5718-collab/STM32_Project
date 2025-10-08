#include "led_pro.h"

/******************************

����˵����
LED2��D2��������PA6
PA6����ڵ͵�ƽ��0����������PA6����ڸߵ�ƽ��1��������
LED3��D3��������PA7
PA7����ڵ͵�ƽ��0����������PA7����ڸߵ�ƽ��1��������

*******************************/
void Led_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;             //����
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;         //���ģʽ
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;        //�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;     //����25MHz
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;          //��������
	
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
    GPIO_Init(GPIOA,&GPIO_InitStruct);

 

}
