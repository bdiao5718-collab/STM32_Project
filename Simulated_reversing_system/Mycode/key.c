#include "key.h"

/*****************************************************
����˵����
KEY0������PE4,KEY1������PE3
����δ���£�PE4Ϊ�ߵ�ƽ��1��
����  ���£�PE4Ϊ�͵�ƽ��0��
******************************************************/
void Key_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStruct;
	//ʱ�ӳ�ʼ��
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_3;         //����4
 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;      //����ģʽ
 GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;      //��������
	
 GPIO_Init(GPIOE,&GPIO_InitStruct);
}